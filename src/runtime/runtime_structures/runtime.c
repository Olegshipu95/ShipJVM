#include "runtime.h"

struct jvm *
new_jvm ()
{
  struct jvm *new_jvm = my_alloc (struct jvm);
  new_jvm->main_class = NULL;
  new_jvm->classloader = NULL;
  return new_jvm;
}

int
run_jvm (struct jvm *jvm)
{
  int err;
  struct rt_method *main_method = NULL;
  err = find_method_in_current_class (jvm->main_class, &main_method, "main",
                                      "([Ljava/lang/String;)V");
  if (err)
    {
      prerr ("Can not find Main method");
      return -1;
    }
  printf ("SUCCESS\n");
  return 0;
}