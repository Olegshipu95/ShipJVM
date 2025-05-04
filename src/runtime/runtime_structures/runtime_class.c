#include "runtime_class.h"

int
jclass_new (struct jclass **jclass, struct class_file *class_file)
{
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

  *jclass = new;
  return -1;
}