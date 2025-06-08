#include "jvm_structure.h"
#include "util.h"
#include "heap.h"

struct jvm*
new_jvm ()
{
  int err;
  struct jvm *new_jvm = my_alloc (struct jvm);
  new_jvm->main_class = NULL;
  new_jvm->classloader = NULL;
  err = heap_init (&new_jvm->heap);
  if (err)
    {
      PANIC ("Can not allocate memory");
    }
  return new_jvm;
}
