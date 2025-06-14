#include "raw_classfile.h"
void
init_class_file (struct class_file *class)
{
  class->magic = 0;
  class->minor_version = 0;
  class->major_version = 0;
  class->constant_pool_count = 0;
  class->constant_pool = 0;
  class->access_flags = 0;
  class->this_class = 0;
  class->super_class = 0;
  class->interfaces_count = 0;
  class->interfaces = 0;
  class->fields_count = 0;
  class->fields = 0;
  class->methods_count = 0;
  class->methods = 0;
  class->attributes_count = 0;
  class->attributes = 0;
}

int
get_constant (struct class_file *class, uint16_t index,
              struct cp_info **cp_info)
{
  if (!class || !class->constant_pool || !cp_info)
    {
      prerr ("Invalid arguments in get_const");
      return EINVAL;
    }

  if (index == 0 || index >= class->constant_pool_count)
    {
      prerr ("Can't take constant by that adress");
      return EINVAL;
    }
  *cp_info = &(class->constant_pool[index - 1]);
  return 0;
}

struct UTF8_info *
validate_constant (struct class_file *class, uint16_t index)
{
  if (!class)
    {
      prerr ("NULL class in validate const");
      return NULL;
    }
  struct cp_info *cp_info = NULL;
  int err = get_constant (class, index, &cp_info);
  if (err != 0 || cp_info == NULL)
    {
      prerr ("get constant - %d", err);
      return NULL;
    }
  if (cp_info->tag != UTF8)
    {
      prerr ("Parse const fail");
      return NULL;
    }
  return &(cp_info->utf8_info);
}
