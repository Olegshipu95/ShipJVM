#include "classfile_parser.h"

int parse_class_file() {
  FILE* file = fopen("tests/Add.class", "rb");
  if (!file) {
    perror("Failed to open file");
    return 1;
  }

  Loader loader = {.file = file, .error = 0};

  uint32_t cafebabe = loader_u4(&loader);
  uint16_t major = loader_u2(&loader);
  uint16_t minor = loader_u2(&loader);
  uint16_t constant_pool_count = loader_u2(&loader);

  parse_const_pool(constant_pool_count, &loader);

  if (loader.error) {
    printf("Error reading file\n");
  } else {
    printf("Magic: 0x%X, Version: %d.%d\n", cafebabe, major, minor);
  }

  fclose(file);
  return 0;
}