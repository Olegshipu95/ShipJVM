#include "classfile_parser.h"
#include "classloader.h"
#include "util.h"
#include <stdint.h>

// Пример использования
int
main (int argc, char *argv[])
{
  printf ("\n");
  if (argc < 3)
    {
      prerr ("Usage: %s <classpath> <classname>", argv[0]);
      return 1;
    }

  struct classloader *classloader = classloader_new();

  classloader_init_dir_paths(classloader, argv[1]);

  struct class_file *class;
  for (int i = 0; i < 50; ++i)
  {
    int err = classloader_load_class(classloader, argv[2], &class);
    if (err) return err;
  }
}
