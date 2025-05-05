#include "runtime_class.h"

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

  memset(new, 0, sizeof(struct jclass));

  new->runtime_cp_count = class_file->constant_pool_count - 1;

  err = new_array_runtime_constpool(&new->runtime_cp, class_file->constant_pool, new->runtime_cp);

  if (err) {
    prerr ("jclass_new: can not parse const pool");
    return err;
  }

  new->access_flags = class_file->access_flags;

  *jclass = new;
  return -1;
}