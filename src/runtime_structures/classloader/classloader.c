#include <stdio.h>

#include "classloader.h"
#include "heap.h"
#include "classfile.h"
#include "classfile_parser.h"
#include "util.h"
#include "rt_attr_parser.h"

// START SECTION INIT_NEW_CLASS_METHODS

int
parse_rt_interfaces (struct runtime_cp *rt_cp, string **new_interfaces,
                     uint16_t *old_interfaces, uint16_t interfaces_count,
                     uint16_t runtime_cp_count)
{
  uint16_t iter;
  int err = 0;
  string *rt_interfaces = my_alloc_array (string, interfaces_count);
  if (rt_interfaces == NULL)
    {
      prerr ("Can not allocate memory for interfaces");
      return ENOMEM;
    }

  for (iter = 0; iter < interfaces_count; ++iter)
    {
      err |= parse_rt_classname (rt_cp, &rt_interfaces[iter],
                                 old_interfaces[iter], runtime_cp_count);
    }
  if (err)
    {
      prerr ("Error in parsing interfaces");
      return -1;
    }

  *new_interfaces = rt_interfaces;
  return 0;
}

int
assign_field_slots (struct classloader *classloader, struct heap *heap,
                    struct jclass *cls, int start_slot)
{
  if (!classloader || !cls)
    return start_slot;

  // Проверка: уже были назначены slot_id?
  int already_initialized = 1;
  for (int i = 0; i < cls->fields_count; i++)
    {
      if (!(cls->fields[i].access_flags & ACC_STATIC))
        {
          if (cls->fields[i].slot_id == UINT32_MAX)
            {
              already_initialized = 0;
              break;
            }
        }
    }

  if (already_initialized)
    {
      uint32_t max_slot = start_slot;

      // Пройтись по всем нестатическим полям и вернуть max(slot_id + 1)
      for (int i = 0; i < cls->fields_count; i++)
        {
          struct rt_field *field = &cls->fields[i];
          if (!(field->access_flags & ACC_STATIC)
              && field->slot_id + 1 > max_slot)
            max_slot = field->slot_id + 1;
        }

      return max_slot;
    }

  // Инициализация суперкласса
  if (cls->super_class)
    {
      struct jclass *super_cls = NULL;
      printf ("Try load super class: %s\n", cls->super_class);
      int err = classloader_load_class (classloader, heap, cls->super_class,
                                        &super_cls);
      if (err)
        {
          // prerr("assign_field_slots: Failed to load superclass %s",
          // cls->super_class);
          PANIC ("assign_field_slots: Failed to load superclass %s",
                 cls->super_class);
          return start_slot;
        }
      printf ("Super %s successfully read\n", cls->super_class);

      start_slot
          = assign_field_slots (classloader, heap, super_cls, start_slot);
    }

  // Назначение slot_id текущим нестатическим полям
  for (int i = 0; i < cls->fields_count; ++i)
    {
      struct rt_field *field = &cls->fields[i];
      if (!(field->access_flags & ACC_STATIC))
        field->slot_id = start_slot++;
    }

  cls->object_fields_count = start_slot;

  return start_slot;
}

void
print_rt_interfaces (string *interf, uint16_t count)
{
  uint16_t iter;
  for (iter = 0; iter < count; iter++)
    {
      printf ("Interface #%-3hu, name - %s\n", iter, interf[iter]);
    }
}

int
set_field_type_from_descriptor (struct rt_field *field)
{
  const char *desc = field->descriptor;
  if (desc == NULL)
    {
      prerr ("Can not parse desc");
      return -1;
    }

  // Если массив, то это объект
  if (desc[0] == '[')
    {
      field->data.type = JOBJECT;
      return 0;
    }

  switch (desc[0])
    {
    case 'I':
    case 'B':
    case 'S':
    case 'C':
    case 'Z':
      field->data = create_variable (JINT);
      break;
    case 'J':
      field->data = create_variable (JLONG);
      break;
    case 'F':
      field->data = create_variable (JFLOAT);
      break;
    case 'D':
      field->data = create_variable (JDOUBLE);
      break;
    case 'L':
      field->data = create_variable (JOBJECT);
      break;
    default:
      prerr ("Unknown field descriptor: %s", desc);
      field->data = create_variable (JINT); // fail-safe
      return -1;
      break;
    }
  return 0;
}

int
parse_rt_fields (struct runtime_cp *rt_cp, struct rt_field **rt_fields,
                 struct field_info *old_field, uint16_t fields_count,
                 uint16_t runtime_cp_count)
{
  uint16_t iter;
  int err = 0;
  printf ("\nStart parsing fields. Number of fields = %hu\n", fields_count);
  struct rt_field *new_fieds = my_alloc_array (struct rt_field, fields_count);
  for (iter = 0; iter < fields_count; ++iter)
    {
      printf ("Fields #%-3hu: ", iter);
      new_fieds[iter].access_flags = old_field[iter].access_flags;
      err |= parse_rt_index_to_string (rt_cp, &new_fieds[iter].name,
                                       old_field[iter].name_index,
                                       runtime_cp_count);
      printf ("Field name: %s, ", new_fieds[iter].name);
      err |= parse_rt_index_to_string (rt_cp, &new_fieds[iter].descriptor,
                                       old_field[iter].descriptor_index,
                                       runtime_cp_count);
      printf ("descriptor: %s, ", new_fieds[iter].descriptor);
      new_fieds[iter].attributes_count = old_field[iter].attributes_count;
      printf ("attr count: %hu \n", new_fieds[iter].attributes_count);
      err |= parse_rt_attributes (
          rt_cp, &new_fieds[iter].attributes, old_field[iter].attributes,
          new_fieds[iter].attributes_count, runtime_cp_count);

      if (err)
        {
          prerr ("can not parse rt fields");
          return err;
        }
      err = set_field_type_from_descriptor (&new_fieds[iter]);
      if (err)
        {
          prerr ("can not parse field type");
          return -1;
        }
      new_fieds[iter].slot_id = UINT32_MAX;
    }
  *rt_fields = new_fieds;
  return 0;
}

int
search_static_native_methods (struct rt_methods_data *methods_data)
{
  uint16_t iter;
  uint16_t static_counter = 0;
  uint16_t native_counter = 0;

  methods_data->native_methods = my_alloc_array (
      struct rt_method *, methods_data->native_methods_count);
  if (methods_data->native_methods == NULL)
    {
      prerr ("Can not allocate memory for methods for native methods");
      return ENOMEM;
    }

  methods_data->static_methods = my_alloc_array (
      struct rt_method *, methods_data->static_methods_count);
  if (methods_data->static_methods == NULL)
    {
      prerr ("Can not allocate memory for methods for static methods");
      return ENOMEM;
    }

  for (iter = 0; iter < methods_data->methods_count; ++iter)
    {
      uint16_t is_static
          = methods_data->methods[iter].access_flags & ACC_STATIC;
      uint16_t is_native
          = methods_data->methods[iter].access_flags & ACC_NATIVE;
      if (is_static)
        {
          if (static_counter == methods_data->static_methods_count)
            {
              prerr ("Mismatch in number of static methods");
              return -1;
            }
          methods_data->static_methods[static_counter]
              = &methods_data->methods[iter];
          ++static_counter;
        }
      if (is_native)
        {
          if (native_counter == methods_data->native_methods_count)
            {
              prerr ("Mismatch in number of native methods");
              return -1;
            }
          methods_data->native_methods[native_counter]
              = &methods_data->methods[iter];
          ++native_counter;
        }
    }
  if (static_counter != methods_data->static_methods_count)
    {
      prerr ("Final static method count mismatch");
      return -1;
    }

  if (native_counter != methods_data->native_methods_count)
    {
      prerr ("Final native method count mismatch");
      return -1;
    }

  return 0;
}

int
parse_rt_methods (struct runtime_cp *rt_cp,
                  struct rt_methods_data *methods_data,
                  struct method_info *old_method, uint16_t runtime_cp_count)
{
  uint16_t methods_count = methods_data->methods_count;
  uint16_t *static_methods_count = &methods_data->static_methods_count;
  uint16_t *native_methods_count = &methods_data->native_methods_count;
  uint16_t iter;
  int err = 0;

  printf ("\nStart parsing methods. Number of methods = %hu\n", methods_count);

  if (static_methods_count == NULL || native_methods_count == NULL)
    {
      prerr ("pointer on countes == NULL");
      return -1;
    }

  *native_methods_count = 0;
  *static_methods_count = 0;

  struct rt_method *new_method
      = my_alloc_array (struct rt_method, methods_count);

  for (iter = 0; iter < methods_count; ++iter)
    {
      uint16_t is_native;
      uint16_t is_static;
      uint16_t is_abstract;

      printf ("Method #%-3hu: ", iter);
      new_method[iter].access_flags = old_method[iter].access_flags;

      // check access flags
      printf ("access: %hu, ", new_method[iter].access_flags);
      is_native = new_method[iter].access_flags & ACC_NATIVE;
      if (is_native)
        {
          *native_methods_count = *native_methods_count + 1;
        }
      is_static = new_method[iter].access_flags & ACC_STATIC;
      if (is_static)
        {
          *static_methods_count = *static_methods_count + 1;
        }
      is_abstract = new_method[iter].access_flags & ACC_ABSTRACT;

      // parse method name
      err |= parse_rt_index_to_string (rt_cp, &new_method[iter].name,
                                       old_method[iter].name_index,
                                       runtime_cp_count);
      printf ("Method name: %s, ", new_method[iter].name);

      // parse method descriptor
      err |= parse_rt_index_to_string (rt_cp, &new_method[iter].descriptor,
                                       old_method[iter].descriptor_index,
                                       runtime_cp_count);
      printf ("descriptor: %s, ", new_method[iter].descriptor);

      // parse attributes
      new_method[iter].attributes_count = old_method[iter].attributes_count;
      printf ("attr count: %hu \n", new_method[iter].attributes_count);
      err |= parse_rt_attributes (
          rt_cp, &new_method[iter].attributes, old_method[iter].attributes,
          new_method[iter].attributes_count, runtime_cp_count);

      if (err)
        {
          prerr ("can not parse rt fields");
          return err;
        }

      // parse Code attribute
      new_method[iter].code_attr = (struct rt_code_attribute *)find_attribute (
          new_method[iter].attributes, new_method[iter].attributes_count,
          ATTRIBUTE_Code);
      if ((is_native || is_abstract))
        {
          if (new_method[iter].code_attr != NULL)
            {
              prerr ("Method %s is abstract/native, but have Code attr",
                     new_method[iter].name);
              return -1;
            }
        }
      else if (new_method[iter].code_attr == NULL)
        {
          prerr ("Method %s must have Code attr", new_method[iter].name);
          return -1;
        }
    }
  methods_data->methods = new_method;
  return 0;
}

int
jclass_new (struct classloader *classloader, struct heap *heap,
            struct jclass **jclass, struct class_file *class_file)
{
  int err;
  if (*jclass != NULL)
    {
      prerr ("JClass has already allocated");
      return EINVAL;
    }

  if (class_file == NULL)
    {
      prerr ("class_file is NULL");
      return EINVAL;
    }

  struct jclass *new = my_alloc (struct jclass);

  memset (new, 0, sizeof (struct jclass));

  new->runtime_cp_count = class_file->constant_pool_count - 1;

  err = new_array_runtime_constpool (
      &new->runtime_cp, class_file->constant_pool, new->runtime_cp_count);

  if (err)
    {
      prerr ("jclass_new: can not parse const pool");
      return err;
    }

  print_runtime_cp (new->runtime_cp, new->runtime_cp_count);

  new->access_flags = class_file->access_flags;

  err = parse_rt_classname (new->runtime_cp, &new->this_class,
                            class_file->this_class, new->runtime_cp_count);

  if (err)
    {
      prerr ("can not convert class.this_class");
      return -1;
    }

  if (class_file->super_class == 0)
    {
      new->super_class = NULL;
    }
  else
    {
      err = parse_rt_classname (new->runtime_cp, &new->super_class,
                                class_file->super_class,
                                new->runtime_cp_count);

      if (err)
        {
          prerr ("can not convert class.super_class");
          return -1;
        }
    }

  printf ("rt class_name : %s\n", new->this_class);

  new->interfaces_count = class_file->interfaces_count;

  err = parse_rt_interfaces (
      new->runtime_cp, &new->interfaces, class_file->interfaces,
      class_file->interfaces_count, new->runtime_cp_count);

  if (err)
    {
      prerr ("can not convert interfaces");
      return -1;
    }

  print_rt_interfaces (new->interfaces, new->interfaces_count);

  new->fields_count = class_file->fields_count;

  err = parse_rt_fields (new->runtime_cp, &new->fields, class_file->fields,
                         class_file->fields_count, new->runtime_cp_count);

  if (err)
    {
      prerr ("can not convert fields");
      return -1;
    }

  assign_field_slots (classloader, heap, new, 0);

  new->methods_data.methods_count = class_file->methods_count;

  err = parse_rt_methods (new->runtime_cp, &new->methods_data,
                          class_file->methods, new->runtime_cp_count);

  if (err)
    {
      prerr ("can not convert methods");
      return -1;
    }

  err = search_static_native_methods (&new->methods_data);
  if (err)
    {
      prerr ("can not correctly find static and native methods");
      return -1;
    }

  printf (" Static methods counter: %hu, native: %hu\n ",
          new->methods_data.static_methods_count,
          new->methods_data.native_methods_count);

  new->attributes_count = class_file->attributes_count;
  err = parse_rt_attributes (new->runtime_cp, &new->attributes,
                             class_file->attributes, new->attributes_count,
                             new->runtime_cp_count);

  if (err)
    {
      prerr ("Can not parse attributes in jclass");
      return -1;
    }

  // try to allocate objects for strings in CP

  if (strcmp (new->this_class, "java/lang/String"))
    {
    }
  else
    {
      struct jclass *string_class;
      int err = classloader_load_class (classloader, heap, "java/lang/String",
                                        &string_class);
      if (err)
        {
          prerr ("Can not load java/lang/String in class %s", new->this_class);
          return -1;
        }
      for (int i = 0; i < new->runtime_cp_count; i++)
        {
          if (new->runtime_cp[i].tag == STRING)
            {
              heap_object *string_object
                  = heap_alloc_object (classloader, heap, string_class);
              if (string_object == NULL)
                {
                  prerr ("Can not allocate string for field: %s",
                         new->runtime_cp[i].string_info.class_raw_data);
                  return -1;
                }
              new->runtime_cp[i].string_info.string_object
                  = (void *)string_object;
            }
        }
    }

  *jclass = new;
  return 0;
}

// END SECTION INIT_NEW_CLASS_METHODS

struct classloader_trie
{

  // next node in current level
  struct classloader_trie *next;

  // node name (package or class name)
  const char *name;

  // children trie nodes
  struct classloader_trie *children;

  // associated value
  // since we may have class named same as a package,
  // both "children" and "value" makes sense to be presented simultaneously
  // because of this, we may always hold only zero or one node with the same
  // name on a same level
  struct jclass *value;
};

// TODO: обработка ошибок выделения памяти (в ядре malloc может кинуть NULL при
// нехватке)

// initialize trie node with the first path of classname
// returns length of the first path
size_t
classloader_trie_init (struct classloader_trie *node, const char *classname)
{
  node->next = NULL;
  node->children = NULL;
  node->value = NULL;

  size_t len = 0;
  while (classname[len] && classname[len] != '.')
    ++len;

  char *name = my_alloc_array (char, len + 1);

  if (name == NULL)
    {
      PANIC ("Can not allocate memory for names in classloader_trie_init");
    }

  memcpy (name, classname, len);
  name[len] = 0;

  node->name = name;
  return len;
}

// find node in trie and create it if needed
struct jclass **
classloader_trie_find (struct classloader_trie **root, const char *classname,
                       int create)
{
  struct classloader_trie **node = root;
  while (*node)
    {
      // check is the current prefix of classname matches with current node
      // name

      size_t len = 0;
      for (const char *it = (*node)->name; *it; ++it, ++len)
        if (classname[len] != *it)
          goto next;

      // are we fully matching the name?
      if (classname[len] && classname[len] != '.')
        {
        next:
          node = &(*node)->next;
          continue;
        }

      // if classname ended, we are reached the searching value
      if (!classname[len])
        return &(*node)->value;

      classname = classname + (len + 1);
      node = &(*node)->children;
    }

  if (!create)
    return NULL;

  while (1)
    {
      *node = my_alloc (struct classloader_trie);
      classname += classloader_trie_init (*node, classname);

      if (!*classname)
        return &(*node)->value;
      ++classname;

      node = &(*node)->children;
    }
}

struct classloader
{

  // NULL-terminated array of directory paths
  const char **dir_paths;

  // trie is built by package names
  struct classloader_trie *classes;
};

struct classloader *
classloader_new (void)
{
  struct classloader *classloader = my_alloc (struct classloader);
  if (!classloader)
    return NULL;

  classloader->dir_paths = NULL;
  classloader->classes = NULL;
  return classloader;
}

void
classloader_init_dir_paths (struct classloader *classloader, const char *paths)
{
  size_t values = 0, started = 0;
  for (const char *it = paths; *it; ++it)
    {
      if (*it == ':')
        {
          values += started;
          started = 0;
          continue;
        }

      started = 1;
    }

  values += started;
  started = 0;

  classloader->dir_paths = my_alloc_array (const char *, values + 1);

  values = 0;
  const char *prev = paths;
  const char *it = paths;
  for (; *it; ++it)
    {
      if (*it == ':')
        {
          if (started)
            {
              const size_t len = it - prev;
              char *const val = my_alloc_array (char, len + 1);
              memcpy (val, prev, len);
              val[len] = 0;

              classloader->dir_paths[values] = val;
            }

          prev = it + 1;

          values += started;
          started = 0;
          continue;
        }

      started = 1;
    }

  if (started)
    {
      const size_t len = it - prev;
      char *const val = my_alloc_array (char, len + 1);
      memcpy (val, prev, len);
      val[len] = 0;

      classloader->dir_paths[values] = val;
      ++values;
    }

  classloader->dir_paths[values] = NULL;
}

char *
classloader_build_path (const char *path, const char *classname)
{
  const size_t path_len = strlen (path);
  const size_t classname_len = strlen (classname);

  char *const res
      = my_alloc_array (char, path_len + 1 + classname_len + 6 + 1);
  memcpy (res, path, path_len);
  res[path_len] = '/';

  for (size_t i = 0; i < classname_len; ++i)
    {
      res[path_len + 1 + i] = classname[i] == '.' ? '/' : classname[i];
    }

  memcpy (res + path_len + 1 + classname_len, ".class", 6);
  res[path_len + 1 + classname_len + 6] = 0;

  return res;
}

int
_classloader_load_class (struct classloader *classloader, struct heap *heap,
                         const char *path, const char *classname,
                         struct jclass **result)
{
  (void)classloader;
  int err;
  char *class_path = classloader_build_path (path, classname);

  printf ("Built path to class: %s\n", class_path);

  struct class_file class;
  err = parse_class_file (&class, class_path);
  if (err)
    {
      prerr ("Can not parse class file in classloader");
      return err;
    }
  struct class_file *classfile = my_alloc (struct class_file);
  *classfile = class;
  struct jclass *entry = 0;
  err = jclass_new (classloader, heap, &entry, classfile);
  if (err)
    {
      prerr ("Can not convert class file to rt class in classloader");
      return err;
    }
  *classloader_trie_find (&classloader->classes, classname, 1) = entry;
  *result = entry;
  return 0;
}

int
classloader_load_class (struct classloader *classloader, struct heap *heap,
                        const char *classname, struct jclass **result)
{
  struct jclass **const found
      = classloader_trie_find (&classloader->classes, classname, 0);
  if (found)
    {
      *result = *found;
      return 0;
    }

  for (const char **it = classloader->dir_paths; *it; ++it)
    {
      const int err = _classloader_load_class (classloader, heap, *it,
                                               classname, result);
      if (err != ENOENT)
        return err;
    }

  return ENOENT;
}
