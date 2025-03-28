#include "classfile_parser.h"



int parse_const_pool(struct class_file* class, Loader* loader) {
  uint16_t pool_count = class->constant_pool_count;
  uint16_t i;
  uint8_t tag;
  int error = 0;

  if (pool_count == 0){
    perror("Constant_pool_count is 0\n");
    return EINVAL;
  }

  if(class->constant_pool != NULL){
    perror("Constant pool has already been initialized\n");
    return EINVAL;
  }

  class->constant_pool = malloc(pool_count);
  
  if(class->constant_pool == NULL){
    perror("can not allocate memory for constant pool\n");
    return ENOMEM;
  }

  for (i = 0; i < pool_count-1; i++) {
    tag = loader_u1(loader);
    class->constant_pool[i].tag = tag;
    printf("I: %hu, tag is - %hhu\n", i, tag);

    switch (tag) {
      
      case UTF8:

        break;
      case INTEGER:
        /* code */
        break;
      case FLOAT:
        /* code */
        break;
      case LONG:
        /* code */
        break;
      case DOUBLE:
        /* code */
        break;
      case CLASS:
        /* code */
        break;
      case STRING:
        /* code */
        break;
      case FIELD_REF:
        /* code */
        break;
      case METHOD_REF:
        /* code */
        break;
      case INTERF_METHOD_REF:
        /* code */
        break;
      case NAME_AND_TYPE:
        /* code */
        break;
      case METHOD_HANDLE:
        /* code */
        break;
      case METHOD_TYPE:
        /* code */
        break;
      case DYNAMIC:
        /* code */
        break;
      case INVOKE_METHOD:
        /* code */
        break;
      case MODULE:
        /* code */
        break;
      case PACKAGE:
          /* code */
        break;
      default:
        printf("ERROR: unsupported tag: %hhu on iteration: %hu\n", tag, i);
        error = EINVAL;
        goto exit;
    }
  }

exit:
  free(class->constant_pool);
  return error;
}

int parse_class_file() {
  int err = 0;
  FILE* file = fopen("tests/Add.class", "rb");
  Loader loader = {.file = file, .error = 0};
  struct class_file class_file;

  if (!file) {
    perror("Failed to open file\n");
    err = EINVAL;
    goto exit;
  }

  init_class_file(&class_file);
  class_file.magic = loader_u4(&loader);
  class_file.major_version = loader_u2(&loader);
  class_file.minor_version = loader_u2(&loader);
  class_file.constant_pool_count = loader_u2(&loader);
  printf("Constant_pool_count is %hu\n", class_file.constant_pool_count);

  if (loader.error) {
    perror("Error reading file\n");
    err = ENOEXEC;
    goto exit;
  }

  err = parse_const_pool(&class_file, &loader);

  if (err != 0) {
    printf("Error after parse const pool is - %d\n", err);
  }

  if (loader.error) {
    perror("Error reading file\n");
    err = ENOEXEC;
    goto exit;
  } else {
    printf("Magic: 0x%X, Version: %hu.%hu\n", class_file.magic,
           class_file.major_version, class_file.minor_version);
  }

exit:
  fclose(file);
  return err;
}