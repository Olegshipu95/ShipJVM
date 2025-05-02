#include "classfile_parser.h"

int
parse_const_pool (struct class_file *class, Loader *loader)
{
  uint16_t pool_count = class->constant_pool_count;
  uint16_t i;
  uint8_t tag;
  int error = 0;

  if (pool_count == 0)
    {
      prerr ("Constant_pool_count is 0");
      return EINVAL;
    }

  if (class->constant_pool != NULL)
    {
      prerr ("Constant pool has already been initialized");
      return EINVAL;
    }

  class->constant_pool = my_alloc_array (struct cp_info, pool_count);

  if (class->constant_pool == NULL)
    {
      prerr ("Can not allocate memory for constant pool");
      return ENOMEM;
    }

  printf ("CONSTANT POOL:\n");

  for (i = 0; i < pool_count - 1; i++)
    {
      tag = loader_u1 (loader);
      class->constant_pool[i].tag = tag;
      printf (" I - %-3hu, tag is - %-3hhu, type - ", i + 1, tag);

      switch (tag)
        {
        case UTF8:
          printf ("Utf8, ");
          read_utf8_info (loader, &(class->constant_pool[i].utf8_info));
          printf ("data - %.*s\n", class->constant_pool[i].utf8_info.lenght,
                  class->constant_pool[i].utf8_info.bytes);
          break;
        case INTEGER:
          printf ("Integer\n");
          read_primitive_info (loader,
                               &(class->constant_pool[i].integer_info.info));
          break;
        case FLOAT:
          printf ("Float\n");
          read_primitive_info (loader,
                               &(class->constant_pool[i].float_info.info));
          break;
        case LONG:
          printf ("Long, ");
          read_big_primitive_info (loader,
                                   &(class->constant_pool[i].long_info.info));
          class->constant_pool[i + 1].long_info.info
              = class->constant_pool[i].long_info.info;

          {
            // for print
            int64_t combined
                = ((int64_t) class->constant_pool[i].long_info.info.high_bytes
                   << 32)
                  | class->constant_pool[i].long_info.info.low_bytes;
            printf ("data - %ldl\n", combined);
          }
          ++i;
          break;
        case DOUBLE:
          printf ("Double, ");
          read_big_primitive_info (
              loader, &(class->constant_pool[i].double_info.info));
          class->constant_pool[i + 1].double_info.info
              = class->constant_pool[i].double_info.info;

          {
            uint64_t combined
                = ((uint64_t) class->constant_pool[i]
                       .double_info.info.high_bytes
                   << 32)
                  | class->constant_pool[i].double_info.info.low_bytes;
            double result;
            memcpy (&result, &combined, sizeof (double));
            printf ("data - %f\n", result);
          }
          ++i;
          break;
        case CLASS:
          printf ("Class\n");
          read_class_info (loader, &(class->constant_pool[i].class_info));
          break;
        case STRING:
          printf ("String\n");
          read_string_info (loader, &(class->constant_pool[i].string_info));
          break;
        case FIELD_REF:
          printf ("Fieldref\n");
          read_ref_type_info (loader,
                              &(class->constant_pool[i].fieldref_info.info));
          break;
        case METHOD_REF:
          printf ("Methodref\n");
          read_ref_type_info (loader,
                              &(class->constant_pool[i].methodref_info.info));
          break;
        case INTERF_METHOD_REF:
          printf ("IntegerMethod\n");
          read_ref_type_info (
              loader, &(class->constant_pool[i].interface_meth_ref_info.info));
          break;
        case NAME_AND_TYPE:
          printf ("NameAndType\n");
          read_name_and_type_info (
              loader, &(class->constant_pool[i].name_and_type_info));
          break;
        case METHOD_HANDLE:
          printf ("MethodHandle\n");
          read_method_handle_info (
              loader, &(class->constant_pool[i].method_handle_info));
          break;
        case METHOD_TYPE:
          printf ("MethodType\n");
          read_method_type_info (loader,
                                 &(class->constant_pool[i].method_type_info));
          break;
        case DYNAMIC:
          printf ("Dynamic\n");
          read_dynamic_info (loader,
                             &(class->constant_pool[i].dynamic_info.info));
          break;
        case INVOKE_METHOD:
          printf ("InvokeMethod\n");
          read_dynamic_info (
              loader, &(class->constant_pool[i].invoke_dynamic_info.info));
          break;
        case MODULE:
          printf ("Module\n");
          read_module_info (loader, &(class->constant_pool[i].module_info));
          break;
        case PACKAGE:
          printf ("Package\n");
          read_package_info (loader, &(class->constant_pool[i].package_info));
          break;
        default:
          printf ("unknown\n");
          prerr (" unsupported tag: %hhu on iteration: %hu", tag, i + 1);
          free (class->constant_pool);
          return EINVAL;
        }
    }
  return error;
}

int
is_string_match (uint8_t *buff, size_t len, const char *expected)
{
  const char *str = (const char *)buff;
  if (len != strlen (expected))
    {
      return 0;
    }
  return memcmp (str, expected, len) == 0;
}

int
parse_class_fields (Loader *loader, struct class_file *class,
                    struct field_info *fields)
{
  int error = 0;
  fields->access_flags = loader_u2 (loader);
  fields->name_index = loader_u2 (loader);
  fields->descriptor_index = loader_u2 (loader);
  fields->attributes_count = loader_u2 (loader);
  error = read_attributes (loader, class, &fields->attributes,
                           fields->attributes_count);
  return error;
}

int
parse_class_methods (Loader *loader, struct class_file *class,
                     struct method_info *method)
{
  printf ("DEBUG METH\n");
  int error = 0;
  method->access_flags = loader_u2 (loader);
  method->name_index = loader_u2 (loader);
  method->descriptor_index = loader_u2 (loader);
  method->attributes_count = loader_u2 (loader);
  error = read_attributes (loader, class, &method->attributes,
                           method->attributes_count);
  return error;
}

int
parse_class_file (struct class_file *class, const char *filename)
{
  int err = 0;
  FILE *file = fopen (filename, "rb");
  if (!file)
    {
      prerr ("Failed to open file");
      goto exit;
    }
  Loader loader = { .file = file, .error = 0 };
  uint16_t iterator;

  if (!file)
    {
      perror ("Failed to open file\n");
      err = EINVAL;
      goto exit;
    }

  init_class_file (class);
  class->magic = loader_u4 (&loader);
  class->major_version = loader_u2 (&loader);
  class->minor_version = loader_u2 (&loader);
  class->constant_pool_count = loader_u2 (&loader);
  printf ("Constant_pool_count is %hu\n", class->constant_pool_count);

  if (loader.error)
    {
      perror ("ERROR: reading file\n");
      err = ENOEXEC;
      goto exit;
    }

  err = parse_const_pool (class, &loader);

  if (err != 0)
    {
      prerr ("after parse const pool is - %d", err);
      err = ENOEXEC;
      goto exit;
    }

  class->access_flags = loader_u2 (&loader);
  class->this_class = loader_u2 (&loader);
  class->super_class = loader_u2 (&loader);
  class->interfaces_count = loader_u2 (&loader);
  class->interfaces = my_alloc_array (uint16_t, class->interfaces_count);

  if (class->interfaces == NULL)
    {
      prerr ("can not malloc data for interfaces");
    }

  for (iterator = 0; iterator < class->interfaces_count; ++iterator)
    {
      class->interfaces[iterator] = loader_u2 (&loader);
    }

  class->fields_count = loader_u2 (&loader);

  class->fields = my_alloc_array (struct field_info, class->fields_count);

  if (class->fields == NULL)
    {
      prerr ("can not malloc data for interfaces");
    }

  printf ("DEBUG: Number of fields: %hu \n", class->fields_count);
  for (iterator = 0; iterator < class->fields_count; ++iterator)
    {
      err |= parse_class_fields (&loader, class, &class->fields[iterator]);
    }

  class->methods_count = loader_u2 (&loader);

  class->methods = my_alloc_array (struct method_info, class->methods_count);

  if (class->methods == NULL)
    {
      prerr ("can not malloc data for methods");
    }

  printf ("DEBUG: Number of methods: %hu\n", class->methods_count);
  for (iterator = 0; iterator < class->methods_count; ++iterator)
    {
      err |= parse_class_methods (&loader, class, &class->methods[iterator]);
    }

  class->attributes_count = loader_u2 (&loader);

  printf ("DEBUG: Number of attributes: %hu\n", class->attributes_count);
  err |= read_attributes (&loader, class, &class->attributes,
                          class->attributes_count);

  if (loader.error)
    {
      perror ("ERROR: Reading file\n");
      err = ENOEXEC;
      goto exit;
    }
  else
    {
      printf ("\n");
      printf ("Fields: %hu, methods: %hu, attributes: %hu\n",
              class->fields_count, class->methods_count, class->attributes_count);
      printf ("Magic: 0x%X, Version: %hu.%hu\n", class->magic,
              class->major_version, class->minor_version);
    }

exit:
  fclose (file);
  return err;
}
