#include <stdint.h>

#include "classfile_parser.h"
#include "classloader.h"
#include "runtime.h"
#include "runtime_class.h"
#include "runtime_constpool.h"
#include "util.h"

// Пример использования
int
main (int argc, char *argv[])
{
  int err = 0;
  printf ("\n");
  if (argc < 3)
    {
      prerr ("Usage: %s <classpath> <classname>", argv[0]);
      return 1;
    }

  struct jvm *jvm = new_jvm ();

  jvm->classloader = classloader_new ();

  classloader_init_dir_paths (jvm->classloader, argv[1]);

  for (int i = 0; i < 50; ++i)
    {
      err = classloader_load_class (jvm->classloader, argv[2],
                                        &jvm->main_class);
      if (err)
        return err;
    }
  err = run_jvm(jvm);
  return err;
}
