#include <stdint.h>

#include "classfile_parser.h"

// Пример использования
int
main (int argc, char *argv[])
{
  printf ("\n");
  if (argc < 2)
    {
      fprintf (stderr, "Usage: %s <classfile>\n", argv[0]);
      return 1;
    }
  return parse_class_file (argc, argv);
}
