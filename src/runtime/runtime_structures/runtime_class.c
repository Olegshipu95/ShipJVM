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
parse_rt_methods (struct runtime_cp *rt_cp, struct rt_method **rt_method,
                  struct method_info *old_method, uint16_t methods_count,
                  uint16_t runtime_cp_count)
{
  uint16_t iter;
  int err = 0;

  printf ("\nStart parsing methods. Number of methods = %hu\n", methods_count);

  struct rt_method *new_method
      = my_alloc_array (struct rt_method, methods_count);

  for (iter = 0; iter < methods_count; ++iter)
    {
      printf ("Method #%-3hu: ", iter);
      new_method[iter].access_flags = old_method[iter].access_flags;
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
    }
  *rt_method = new_method;
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

  new->methods_count = class_file->methods_count;

  err = parse_rt_methods (new->runtime_cp, &new->methods, class_file->methods,
                          class_file->methods_count, new->runtime_cp_count);

  *jclass = new;
  return 0;
}