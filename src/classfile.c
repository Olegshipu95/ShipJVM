#include "classfile.h"
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
  if (index == 0 || index > class->constant_pool_count)
    {
      printf ("Can't take constant by that adress");
      return EINVAL;
    }

  *cp_info = &(class->constant_pool[index - 1]);

  return 0;
}