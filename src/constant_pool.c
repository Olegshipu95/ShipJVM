#include "constant_pool.h"

int
read_utf8_info (Loader *loader, struct UTF8_info *utf8)
{
  uint16_t i;

  utf8->lenght = loader_u2 (loader);
  utf8->bytes = (uint8_t *)malloc ((size_t)utf8->lenght);

  if (utf8->bytes == NULL)
    {
      printf ("ERROR: Can't allocate memory for string\n");
      return EINVAL;
    }

  for (i = 0; i < utf8->lenght; i++)
    {
      utf8->bytes[i] = loader_u1 (loader);
    }

  return 0;
}

int
read_primitive_info (Loader *loader, struct abstract_primitive *info)
{
  info->bytes = loader_u4 (loader);
  return 0;
}

int
read_big_primitive_info (Loader *loader, struct abstract_big_primitive *info)
{
  info->high_bytes = loader_u4 (loader);
  info->low_bytes = loader_u4 (loader);
  return 0;
}

int
read_class_info (Loader *loader, struct class_info *info)
{
  info->name_index = loader_u2 (loader);
  return 0;
}

int
read_string_info (Loader *loader, struct string_info *info)
{
  info->string_index = loader_u2 (loader);
  return 0;
}

int
read_ref_type_info (Loader *loader, struct abstract_ref_type *info)
{
  info->class_index = loader_u2 (loader);
  info->name_and_type_index = loader_u2 (loader);
  return 0;
}

int
read_name_and_type_info (Loader *loader, struct name_and_type_info *info)
{
  info->name_index = loader_u2 (loader);
  info->descripror_index = loader_u2 (loader);
  return 0;
}

int
read_method_handle_info (Loader *loader, struct method_handle_info *info)
{
  info->reference_kind = loader_u1 (loader);
  info->reference_index = loader_u2 (loader);
  return 0;
}

int
read_method_type_info (Loader *loader, struct method_type_info *info)
{
  info->descriptor_index = loader_u2 (loader);
  return 0;
}

int
read_dynamic_info (Loader *loader, struct absract_dynamic_info *info)
{
  info->bootstrap_method_attr_index = loader_u2 (loader);
  info->name_and_type_index = loader_u2 (loader);
  return 0;
}

int
read_module_info (Loader *loader, struct module_info *info)
{
  info->name_index = loader_u2 (loader);
  return 0;
}

int
read_package_info (Loader *loader, struct package_info *info)
{
  info->name_index = loader_u2 (loader);
  return 0;
}

struct UTF8_info *
validate_constant (struct class_file *class, uint16_t index)
{
  struct cp_info **cp_info = NULL;
  int err = get_constant (class, index, cp_info);
  if (err != 0 || cp_info == NULL)
    {
      printf ("ERROR: %d", err);
      return NULL;
    }
  if ((*cp_info)->tag != UTF8)
    {
      printf ("ERROR: parse const fail");
      return NULL;
    }
  return &((*cp_info)->utf8_info);
}