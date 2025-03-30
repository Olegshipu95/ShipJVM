#include "classfile_parser.h"

int is_string_match(const char* str, size_t len, const char* expected) {
  if (len != strlen(expected)) {
      return 0;
  }
  return memcmp(str, expected, len) == 0;
}

int parse_attributes(Loader* loader, struct class_file* class, struct attribute_info *attr){
  int iter;
  int err = 0;
  
  if(attr==NULL){
    printf("ERROR: Attributes array is null");
    return EINVAL;
  }

  attr->attribute_name_index = loader_u2(loader);
  attr->attribute_length = loader_u4(loader);
  struct UTF8_info* UTF8 = validate_constant(class, attr->attribute_name_index);

  if(UTF8 == NULL){
    printf("ERROR while reading attr name");
    err = 1;
  }
  attr->info = malloc((size_t)(attr->attribute_length) * sizeof(struct attribute_info));

  if (attr->info){
    printf("ERROR after malloc for attr");
    err = 1;
  }

  

  for(iter = 0; iter < class->attributes_count; iter++){
    if(is_string_match(UTF8->bytes, UTF8->lenght, "Code")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif
      struct code_attribute* code = (struct code_attribute*)attr->info;

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "ConstantValue")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "StackMapTable")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif
      
    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "BootstrapMethods")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "NestHost")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "NestMembers")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "PermittedSubclasses")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "Exceptions")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "InnerClasses")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "EnclosingMethod")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "Synthetic")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "Signature")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "Record")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "SourceFile")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "LineNumberTable")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "LocalVariableTable")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "SourceDebugExtension")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "Deprecated")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "RuntimeVisibleAnnotations")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "RuntimeInvisibleAnnotations")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "RuntimeVisibleParameterAnnotations")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "RuntimeInvisibleParameterAnnotations")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "RuntimeVisibleTypeAnnotations")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "RuntimeInvisibleTypeAnnotations")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "AnnotationDefault")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "MethodParameters")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "Module")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "ModulePackages")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else if(is_string_match(UTF8->bytes, UTF8->lenght, "ModuleMainClass")){
      #ifdef DEBUG
      assert((size_t)(attr->attribute_length) * sizeof(struct attribute_info)
       == sizeof(struct code_attribute))
      #endif

    }
    else {
      print("ERROR!!!");
    }
  }

  return 0;
}

int parse_class_fields(Loader* loader, struct field_info* fields) {
  fields->access_flags = loader_u2(loader);
  fields->name_index = loader_u2(loader);
  fields->descriptor_index = loader_u2(loader);
  fields->attributes_count = loader_u2(loader);
  fields->access_flags = loader_u2(loader);
  fields->attributes = malloc(sizeof(struct attribute_info) *
                        (size_t)(fields->attributes_count));
  if(fields->attributes == NULL){
    printf("ERROR: can't allocate memory for fields attributes");
    return ENOMEM;
  }
  int err = parse_attributes(loader, fields->attributes_count, fields->attributes);
  return err;
}

int parse_const_pool(struct class_file* class, Loader* loader) {
  uint16_t pool_count = class->constant_pool_count;
  uint16_t i;
  uint8_t tag;
  int error = 0;

  if (pool_count == 0) {
    perror("Constant_pool_count is 0\n");
    return EINVAL;
  }

  if (class->constant_pool != NULL) {
    perror("Constant pool has already been initialized\n");
    return EINVAL;
  }

  class->constant_pool = malloc(pool_count * sizeof(struct cp_info));

  if (class->constant_pool == NULL) {
    perror("can not allocate memory for constant pool\n");
    return ENOMEM;
  }

  printf("CONSTANT POOL:\n");

  for (i = 0; i < pool_count - 1; i++) {
    tag = loader_u1(loader);
    class->constant_pool[i].tag = tag;
    printf("I: %hu, tag is - %hhu, type - ", i, tag);

    switch (tag) {
      case UTF8:
        printf("UTF8, ");
        read_utf8_info(loader, &(class->constant_pool[i].utf8_info));
        printf("data - %.*s\n", class->constant_pool[i].utf8_info.lenght,
               class->constant_pool[i].utf8_info.bytes);
        break;
      case INTEGER:
        printf("INTEGER\n");
        read_primitive_info(loader,
                            &(class->constant_pool[i].integer_info.info));
        break;
      case FLOAT:
        printf("FLOAT\n");
        read_primitive_info(loader, &(class->constant_pool[i].float_info.info));
        break;
      case LONG:
        printf("LONG\n");
        read_big_primitive_info(loader,
                                &(class->constant_pool[i].long_info.info));
        break;
      case DOUBLE:
        printf("DOUBLE\n");
        read_big_primitive_info(loader,
                                &(class->constant_pool[i].double_info.info));
        break;
      case CLASS:
        printf("CLASS\n");
        read_class_info(loader, &(class->constant_pool[i].class_info));
        break;
      case STRING:
        printf("STRING\n");
        read_string_info(loader, &(class->constant_pool[i].string_info));
        break;
      case FIELD_REF:
        printf("FIELD_RED\n");
        read_ref_type_info(loader,
                           &(class->constant_pool[i].fieldref_info.info));
        break;
      case METHOD_REF:
        printf("METHOD_REF\n");
        read_ref_type_info(loader,
                           &(class->constant_pool[i].methodref_info.info));
        break;
      case INTERF_METHOD_REF:
        printf("INTEGER_METHOD\n");
        read_ref_type_info(
            loader, &(class->constant_pool[i].interface_meth_ref_info.info));
        break;
      case NAME_AND_TYPE:
        printf("NAME_AND_TYPE\n");
        read_name_and_type_info(loader,
                                &(class->constant_pool[i].name_and_type_info));
        break;
      case METHOD_HANDLE:
        printf("METHOD_HANDLE\n");
        read_method_handle_info(loader,
                                &(class->constant_pool[i].method_handle_info));
        break;
      case METHOD_TYPE:
        printf("METHOD_TYPE\n");
        read_method_type_info(loader,
                              &(class->constant_pool[i].method_type_info));
        break;
      case DYNAMIC:
        printf("DYNAMIC\n");
        read_dynamic_info(loader, &(class->constant_pool[i].dynamic_info.info));
        break;
      case INVOKE_METHOD:
        printf("INVOKE_METHOD\n");
        read_dynamic_info(loader,
                          &(class->constant_pool[i].invoke_dynamic_info.info));
        break;
      case MODULE:
        printf("MODULE\n");
        read_module_info(loader, &(class->constant_pool[i].module_info));
        break;
      case PACKAGE:
        printf("PACKAGE\n");
        read_package_info(loader, &(class->constant_pool[i].package_info));
        break;
      default:
        printf("unknown\n, ERROR: unsupported tag: %hhu on iteration: %hu\n",
               tag, i);
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
  struct class_file class;
  uint16_t iterator;

  if (!file) {
    perror("Failed to open file\n");
    err = EINVAL;
    goto exit;
  }

  init_class_file(&class);
  class.magic = loader_u4(&loader);
  class.major_version = loader_u2(&loader);
  class.minor_version = loader_u2(&loader);
  class.constant_pool_count = loader_u2(&loader);
  printf("Constant_pool_count is %hu\n", class.constant_pool_count);

  if (loader.error) {
    perror("Error reading file\n");
    err = ENOEXEC;
    goto exit;
  }

  err = parse_const_pool(&class, &loader);

  if (err != 0) {
    printf("Error after parse const pool is - %d\n", err);
  }

  class.access_flags = loader_u2(&loader);
  class.this_class = loader_u2(&loader);
  class.super_class = loader_u2(&loader);
  class.interfaces_count = loader_u2(&loader);
  class.interfaces = malloc(class.interfaces_count * sizeof(uint16_t));

  if (class.interfaces == NULL) {
    printf("ERROR: can not malloc data for interfaces");
  }

  for (iterator = 0; iterator < class.interfaces_count; ++iterator) {
    class.interfaces[iterator] = loader_u2(&loader);
  }

  class.fields_count = loader_u2(&loader);

  class.fields = malloc(sizeof(struct field_info) * class.fields_count);

  if (class.fields == NULL) {
    printf("ERROR: can not malloc data for interfaces");
  }

  // for (iterator = 0; iterator < class.fields_count; ++iterator) {
  //   class.fields[iterator];
  // }

  if (loader.error) {
    perror("Error reading file\n");
    err = ENOEXEC;
    goto exit;
  } else {
    printf("Magic: 0x%X, Version: %hu.%hu\n", class.magic, class.major_version,
           class.minor_version);
  }

exit:
  fclose(file);
  return err;
}