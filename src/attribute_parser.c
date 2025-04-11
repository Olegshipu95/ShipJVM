#include "attribute_parser.h"

struct attribute_info* parse_attribute(Loader* loader,
                                       struct class_file* class) {
  int iter;
  int err = 0;

  uint16_t attribute_name_index = loader_u2(loader);
  uint16_t attribute_length = loader_u4(loader);
  struct UTF8_info* UTF8 = validate_constant(class, attribute_name_index);

  if (UTF8 == NULL) {
    printf("ERROR while reading attr name");
    err = ENOMEM;
    return NULL;
  }

  if (is_string_match(UTF8->bytes, UTF8->lenght, "ConstantValue")) {
    struct ConstantValue_attribute* attr =
        malloc(sizeof(struct ConstantValue_attribute));
    if (attr == NULL) {
      printf("ERROR while allocating memory for ConstantValue_attribute");
      err = ENOMEM;
      return NULL;
    }
    attr->info.attribute_name_index = attribute_name_index;
    attr->info.attribute_length = attribute_length;
    err = parse_ConstantValue_at(loader, attr);
    if (err != 0) {
      printf("ERROR while parsing ConstantValue_attribute");
      return NULL;
    }
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "Code")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "StackMapTable")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "NestHost")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "NestMembers")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght,
                             "PermittedSubclasses")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "Exceptions")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "InnerClasses")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "EnclosingMethod")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "Synthetic")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "Signature")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "Record")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "SourceFile")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "LineNumberTable")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "LocalVariableTable")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght,
                             "SourceDebugExtension")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "Deprecated")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght,
                             "RuntimeVisibleAnnotations")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght,
                             "RuntimeInvisibleAnnotations")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght,
                             "RuntimeVisibleParameterAnnotations")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght,
                             "RuntimeInvisibleParameterAnnotations")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght,
                             "RuntimeVisibleTypeAnnotations")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght,
                             "RuntimeInvisibleTypeAnnotations")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "AnnotationDefault")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "MethodParameters")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "Module")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "ModulePackages")) {
  } else if (is_string_match(UTF8->bytes, UTF8->lenght, "ModuleMainClass")) {
  } else {
    print("ERROR!!!");
  }

  return 0;
}

int read_attributes(Loader* loader, struct class_file* class,
                    struct attribute_info*** info, uint16_t count) {
  struct attribute_info** attributes =
      malloc(sizeof(struct attribute_info*) * (size_t)(count));
  int iter = 0;
  if (attributes == NULL) {
    printf("ERROR: can't allocate memory for fields attributes");
    return ENOMEM;
  }
  for (iter; iter < count; iter++) {
    attributes[iter] = parse_attribute(loader, class);
  }
  return 0;
}

int parse_ConstantValue_at(Loader* loader,
                           struct ConstantValue_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  attr->constant_value_index = loader_u2(loader);
  return 0;
}

int parse_Code_attribute(Loader* loader, struct class_file* class,
                         struct Code_attribute* attr) {
  int error = 0;
  uint32_t iter = 0;
  if (attr == NULL) {
    return EINVAL;
  }
  attr->max_stack = loader_u2(loader);
  attr->max_locals = loader_u2(loader);
  attr->code_length = loader_u4(loader);
  attr->code = malloc(attr->code_length);
  if (attr->code == NULL) {
    return ENOMEM;
  }
  for (iter; iter < attr->code_length; ++iter) {
    attr->code[iter] = loader_u1(loader);
  }
  attr->exception_table_length = loader_u2(loader);
  attr->table =
      malloc(sizeof(struct exception_table) * attr->exception_table_length);
  if (attr->table == NULL) {
    free(attr->code);
    return ENOMEM;
  }
  for (iter = 0; iter < attr->exception_table_length; ++attr) {
    attr->table[iter].start_pc = loader_u2(loader);
    attr->table[iter].end_pc = loader_u2(loader);
    attr->table[iter].handler_pc = loader_u2(loader);
    attr->table[iter].catch_type = loader_u2(loader);
  }
  attr->attributes_count = loader_u2(loader);
  error =
      read_attributes(loader, class, &attr->attributes, attr->attributes_count);

  return error;
}

int parse_StackMapTable_at(Loader* loader,
                           struct StackMapTable_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_BootstrapMethods_at(Loader* loader,
                              struct BootstrapMethods_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_NestHost_at(Loader* loader, struct NestHost_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_NestMembers_at(Loader* loader, struct NestMembers_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_PermittedSubclasses_at(Loader* loader,
                                 struct PermittedSubclasses_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_Exceptions_at(Loader* loader, struct Exceptions_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_InnerClasses_at(Loader* loader, struct InnerClasses_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_EnclosingMethod_at(Loader* loader,
                             struct EnclosingMethod_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_Synthetic_at(Loader* loader, struct Synthetic_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_Signature_at(Loader* loader, struct Signature_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_Record_at(Loader* loader, struct Record_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_SourceFile_at(Loader* loader, struct SourceFile_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_lineNumberTable_at(Loader* loader,
                             struct LineNumberTable_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_LocalVariableTable_at(Loader* loader,
                                struct LocalVariableTable_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_LocalVariableTypeTable_at(
    Loader* loader, struct LocalVariableTypeTable_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_SourceDebugExtension_at(Loader* loader,
                                  struct SourceDebugExtension_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_Deprecated_at(Loader* loader, struct Deprecated_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_RuntimeInvisibleAnnotations_at(
    Loader* loader, struct RuntimeInvisibleAnnotations_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_RuntimeVisibleParameterAnnotations_at(
    Loader* loader, struct RuntimeVisibleParameterAnnotations_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_RuntimeInvisibleParameterAnnotations_at(
    Loader* loader,
    struct RuntimeInvisibleParameterAnnotations_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_RuntimeVisibleTypeAnnotations_at(
    Loader* loader, struct RuntimeVisibleTypeAnnotations_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_RuntimeInvisibleTypeAnnotations_at(
    Loader* loader, struct RuntimeInvisibleTypeAnnotations_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_AnnotationDefault_at(Loader* loader,
                               struct AnnotationDefault_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_MethodParameters_at(Loader* loader,
                              struct MethodParameters_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_Module_at(Loader* loader, struct Module_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_ModulePackages_at(Loader* loader,
                            struct ModulePackages_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}

int parse_ModuleMainClass_at(Loader* loader,
                             struct ModuleMainClass_attribute* attr) {
  if (attr == NULL) {
    return EINVAL;
  }
  return 0;
}