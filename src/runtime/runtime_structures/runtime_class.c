#include "runtime_class.h"



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
      err |= parse_rt_index_to_string (rt_cp, &new_fieds->name,
                                       old_field[iter].name_index,
                                       runtime_cp_count);
      printf ("Field name: %s, ", new_fieds->name);
      err |= parse_rt_index_to_string (rt_cp, &new_fieds->descriptor,
                                       old_field[iter].descriptor_index,
                                       runtime_cp_count);
      printf ("descriptor: %s, ", new_fieds->descriptor);
      new_fieds[iter].attributes_count = new_fieds[iter].attributes_count;
      printf ("attr count: %hu \n", new_fieds[iter].attributes_count);
      err |= parse_rt_attributes (
          rt_cp, &new_fieds[iter].attributes, old_field[iter].attributes,
          new_fieds[iter].attributes_count, runtime_cp_count);

      if (err)
        {
          prerr ("can not parse rt fields");
          return err;
        }
    }
  *rt_fields = new_fieds;
  return 0;
}

int
search_static_native_methods (struct rt_methods_data* methods_data)
{
  uint16_t iter;
  uint16_t static_counter = 0;
  uint16_t native_counter = 0;

  methods_data->native_methods = my_alloc_array(struct rt_method *, methods_data->native_methods_count);
  if (methods_data->native_methods == NULL)
  {
    prerr ("Can not allocate memory for methods for native methods");
    return ENOMEM;
  }

  methods_data->static_methods = my_alloc_array(struct rt_method *, methods_data->static_methods_count);
  if (methods_data->static_methods == NULL)
  {
    prerr ("Can not allocate memory for methods for static methods");
    return ENOMEM;
  }

  for (iter = 0; iter < methods_data->methods_count; ++iter)
  {
    uint16_t is_static = methods_data->methods[iter].access_flags & ACC_STATIC;
    uint16_t is_native = methods_data->methods[iter].access_flags & ACC_NATIVE;
    if (is_static)
    {
      if (static_counter == methods_data->static_methods_count){
        prerr ("Mismatch in number of static methods");
        return -1;
      }
      methods_data->static_methods[static_counter] = &methods_data->methods[iter];
      ++static_counter;
    }
    if (is_native)
    {
      if (native_counter == methods_data->native_methods_count){
        prerr ("Mismatch in number of native methods");
        return -1;
      }
      methods_data->native_methods[static_counter] = &methods_data->methods[iter];
      ++static_counter;
    }
  }
  return 0;
}

int
parse_rt_methods (struct runtime_cp *rt_cp, struct rt_methods_data *methods_data,
                  struct method_info *old_method,
                  uint16_t runtime_cp_count)
{
  uint16_t methods_count = methods_data->methods_count;
  uint16_t* static_methods_count = &methods_data->static_methods_count;
  uint16_t* native_methods_count = &methods_data->native_methods_count;
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
      printf ("Method #%-3hu: ", iter);
      new_method[iter].access_flags = old_method[iter].access_flags;
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
      err |= parse_rt_index_to_string (rt_cp, &new_method->name,
                                       old_method[iter].name_index,
                                       runtime_cp_count);

      printf ("Method name: %s, ", new_method->name);
      err |= parse_rt_index_to_string (rt_cp, &new_method->descriptor,
                                       old_method[iter].descriptor_index,
                                       runtime_cp_count);

      printf ("descriptor: %s, ", new_method->descriptor);
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
      if (is_native && !is_static)
        {
          prerr (" Method %s must be static", new_method->name);
          return -1;
        }
    }
  methods_data->methods = new_method;
  return 0;
}

int
jclass_new (struct jclass **jclass, struct class_file *class_file)
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

  err = parse_rt_fields (new->runtime_cp, &new->fields, class_file->fields,
                         class_file->fields_count, new->runtime_cp_count);

  if (err)
    {
      prerr ("can not convert fields");
      return -1;
    }

  new->methods_data.methods_count = class_file->methods_count;

  err = parse_rt_methods (new->runtime_cp, &new->methods_data, class_file->methods, new->runtime_cp_count);

  if (err)
    {
      prerr ("can not convert methods");
      return -1;
    }

  err = search_static_native_methods(&new->methods_data);
  if (err)
  {
    prerr ("can not correctly find static and native methods");
    return -1;
  }

  printf (" Static methods counter: %hu, native: %hu\n ",
          new->methods_data.static_methods_count, new->methods_data.native_methods_count);

  new->attributes_count = class_file->attributes_count;
  err = parse_rt_attributes (new->runtime_cp, &new->attributes,
                             class_file->attributes, new->attributes_count,
                             new->runtime_cp_count);

  if (err)
    {
      prerr ("Can not parse attributes in jclass");
      return -1;
    }

  *jclass = new;
  return 0;
}