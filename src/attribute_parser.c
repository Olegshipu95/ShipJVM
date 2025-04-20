#include "attribute_parser.h"

struct attribute_info *
parse_attribute (Loader *loader, struct class_file *class)
{
  printf ("DEBUG: Start parsing attributes\n");
  int err = 0;

  uint16_t attribute_name_index = loader_u2 (loader);
  uint16_t attribute_length = loader_u4 (loader);
  struct UTF8_info *UTF8 = validate_constant (class, attribute_name_index);

  if (UTF8 == NULL)
    {
      printf ("ERROR while reading attr name\n");
      err = ENOMEM;
      return NULL;
    }

  if (UTF8 && UTF8->bytes)
    {
      printf ("UTF IS - %.*s\n", UTF8->lenght, UTF8->bytes);
    }
  else
    {
      printf ("UTF8 string is NULL or invalid!\n");
    }
  printf ("DEBUG POINT\n");

  if (is_string_match (UTF8->bytes, UTF8->lenght, "ConstantValue"))
    {
      struct ConstantValue_attribute *attr
          = malloc (sizeof (struct ConstantValue_attribute));
      if (attr == NULL)
        {
          printf (
              "ERROR while allocating memory for ConstantValue_attribute\n");
          err = ENOMEM;
          return NULL;
        }
      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_ConstantValue_at (loader, attr);
      if (err != 0)
        {
          printf ("ERROR while parsing ConstantValue_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "Code"))
    {
      struct Code_attribute *attr = malloc (sizeof (struct Code_attribute));
      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for Code_attribute\n");
          err = ENOMEM;
          return NULL;
        }
      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_Code_attribute (loader, class, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing Code_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "StackMapTable"))
    {
      struct StackMapTable_attribute *attr
          = malloc (sizeof (struct StackMapTable_attribute));
      if (attr == NULL)
        {
          printf (
              "ERROR while allocating memory for StackMapTable_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_StackMapTable_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing StackMapTable\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "BootstrapMethods"))
    {
      struct BootstrapMethods_attribute *attr
          = malloc (sizeof (struct BootstrapMethods_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "BootstrapMethods_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;

      err = parse_BootstrapMethods_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing BootstrapMethods_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "NestHost"))
    {
      struct NestHost_attribute *attr
          = malloc (sizeof (struct NestHost_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for NestHost_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;

      err = parse_NestHost_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing NestHost_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "NestMembers"))
    {
      struct NestMembers_attribute *attr
          = malloc (sizeof (struct NestMembers_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for NestMembers_attribute\n");
          err = ENOMEM;
          return NULL;
        }
      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;

      if (err != 0)
        {
          printf ("ERROR while parsing NestMembers_attribute\n");
          return NULL;
        }

      err = parse_NestMembers_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing NestMembers_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "PermittedSubclasses"))
    {
      struct PermittedSubclasses_attribute *attr
          = malloc (sizeof (struct PermittedSubclasses_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "PermittedSubclasses_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;

      err = parse_PermittedSubclasses_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing PermittedSubclasses_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "Exceptions"))
    {
      struct Exceptions_attribute *attr
          = malloc (sizeof (struct Exceptions_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for Exceptions_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;

      err = parse_Exceptions_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing Exceptions_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght,
                            "InnerClasses_attribute"))
    {
      struct InnerClasses_attribute *attr
          = malloc (sizeof (struct InnerClasses_attribute));

      if (attr == NULL)
        {
          printf (
              "ERROR while allocating memory for InnerClasses_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;

      err = parse_InnerClasses_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing InnerClasses_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "EnclosingMethod"))
    {

      struct EnclosingMethod_attribute *attr
          = malloc (sizeof (struct EnclosingMethod_attribute));

      if (attr == NULL)
        {
          printf (
              "ERROR while allocating memory for EnclosingMethod_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;

      err = parse_EnclosingMethod_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing EnclosingMethod_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "Synthetic"))
    {
      struct Synthetic_attribute *attr
          = malloc (sizeof (struct Synthetic_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for Synthetic_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;

      err = parse_Synthetic_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing Synthetic_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "Signature"))
    {
      struct Signature_attribute *attr
          = malloc (sizeof (struct Signature_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for Signature_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_Signature_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing Signature_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "Record"))
    {
      struct Record_attribute *attr
          = malloc (sizeof (struct Record_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for Record_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_Record_at (loader, class, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing Record_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "SourceFile"))
    {
      struct SourceFile_attribute *attr
          = malloc (sizeof (struct SourceFile_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for SourceFile_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;

      err = parse_SourceFile_at (loader, attr);
      if (err != 0)
        {
          printf ("ERROR while parsing SourceFile_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "LineNumberTable"))
    {
      struct LineNumberTable_attribute *attr
          = malloc (sizeof (struct LineNumberTable_attribute));

      if (attr == NULL)
        {
          printf (
              "ERROR while allocating memory for LineNumberTable_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_LineNumberTable_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing LineNumberTable_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "LocalVariableTable"))
    {
      struct LocalVariableTable_attribute *attr
          = malloc (sizeof (struct LocalVariableTable_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "LocalVariableTable_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;

      err = parse_LocalVariableTable_at (loader, attr);
      if (err != 0)
        {
          printf ("ERROR while parsing LocalVariableTable_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght,
                            "LocalVariableTypeTable"))
    {
      struct LocalVariableTypeTable_attribute *attr
          = malloc (sizeof (struct LocalVariableTypeTable_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "LocalVariableTypeTable_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_LocalVariableTypeTable_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing LocalVariableTypeTable_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "SourceDebugExtension"))
    {
      struct SourceDebugExtension_attribute *attr
          = malloc (sizeof (struct SourceDebugExtension_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "SourceDebugExtension_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_SourceDebugExtension_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing SourceDebugExtension_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "Deprecated"))
    {
      struct Deprecated_attribute *attr
          = malloc (sizeof (struct Deprecated_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for Deprecated_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_Deprecated_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing Deprecated_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght,
                            "RuntimeVisibleAnnotations"))
    {
      struct RuntimeVisibleAnnotations_attribute *attr
          = malloc (sizeof (struct RuntimeVisibleAnnotations_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "RuntimeVisibleAnnotations_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_RuntimeVisibleAnnotations_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing RuntimeVisibleAnnotations_attribute\n");
          return NULL;
        }

      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght,
                            "RuntimeInvisibleAnnotations"))
    {
      struct RuntimeInvisibleAnnotations_attribute *attr
          = malloc (sizeof (struct RuntimeInvisibleAnnotations_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "RuntimeInvisibleAnnotations_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_RuntimeInvisibleAnnotations_at (loader, attr);
      if (err != 0)
        {
          printf (
              "ERROR while parsing RuntimeInvisibleAnnotations_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght,
                            "RuntimeVisibleParameterAnnotations"))
    {
      struct RuntimeVisibleParameterAnnotations_attribute *attr = malloc (
          sizeof (struct RuntimeVisibleParameterAnnotations_attribute));
      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "RuntimeVisibleParameterAnnotations_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_RuntimeVisibleParameterAnnotations_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing "
                  "RuntimeVisibleParameterAnnotations_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght,
                            "RuntimeInvisibleParameterAnnotations"))
    {
      struct RuntimeInvisibleParameterAnnotations_attribute *attr = malloc (
          sizeof (struct RuntimeInvisibleParameterAnnotations_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "RuntimeInvisibleParameterAnnotations_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_RuntimeInvisibleParameterAnnotations_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing "
                  "RuntimeInvisibleParameterAnnotations_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght,
                            "RuntimeVisibleTypeAnnotations"))
    {
      struct RuntimeVisibleTypeAnnotations_attribute *attr
          = malloc (sizeof (struct RuntimeVisibleTypeAnnotations_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "RuntimeVisibleTypeAnnotations_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_RuntimeVisibleTypeAnnotations_at (loader, attr);

      if (err != 0)
        {
          printf (
              "ERROR while parsing RuntimeVisibleTypeAnnotations_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght,
                            "RuntimeInvisibleTypeAnnotations"))
    {
      struct RuntimeInvisibleTypeAnnotations_attribute *attr
          = malloc (sizeof (struct RuntimeInvisibleTypeAnnotations_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "RuntimeInvisibleTypeAnnotations_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      if (err != 0)
        {
          printf ("ERROR while parsing "
                  "RuntimeInvisibleTypeAnnotations_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "AnnotationDefault"))
    {
      // TODO
      struct AnnotationDefault_attribute *attr
          = malloc (sizeof (struct AnnotationDefault_attribute));

      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "AnnotationDefault_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_AnnotationDefault_at (loader, attr);

      if (err != 0)
        {
          printf ("ERROR while parsing AnnotationDefault_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "MethodParameters"))
    {
      struct MethodParameters_attribute *attr
          = malloc (sizeof (struct MethodParameters_attribute));
      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "MethodParameters_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_MethodParameters_at (loader, attr);
      if (err != 0)
        {
          printf ("ERROR while parsing MethodParameters_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "Module"))
    {
      struct Module_attribute *attr
          = malloc (sizeof (struct Module_attribute));
      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "Module_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_Module_at (loader, attr);
      if (err != 0)
        {
          printf ("ERROR while parsing Module_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "ModulePackages"))
    {
      struct ModulePackages_attribute *attr
          = malloc (sizeof (struct ModulePackages_attribute));
      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "ModulePackages_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_ModulePackages_at (loader, attr);
      if (err != 0)
        {
          printf ("ERROR while parsing ModulePackages_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else if (is_string_match (UTF8->bytes, UTF8->lenght, "ModuleMainClass"))
    {
      struct ModuleMainClass_attribute *attr
          = malloc (sizeof (struct ModuleMainClass_attribute));
      if (attr == NULL)
        {
          printf ("ERROR while allocating memory for "
                  "ModuleMainClass_attribute\n");
          err = ENOMEM;
          return NULL;
        }

      attr->info.attribute_name_index = attribute_name_index;
      attr->info.attribute_length = attribute_length;
      err = parse_ModuleMainClass_at (loader, attr);
      if (err != 0)
        {
          printf ("ERROR while parsing ModuleMainClass_attribute\n");
          return NULL;
        }
      return (struct attribute_info *)attr;
    }
  else
    {
      printf ("ERROR!!!\n");
      return NULL;
    }

  return 0;
}

int
read_attributes (Loader *loader, struct class_file *class,
                 struct attribute_info ***info, uint16_t count)
{
  printf ("DEBUG: Start read attributes\n");
  struct attribute_info **attributes
      = malloc (sizeof (struct attribute_info *) * (size_t)(count));
  int iter;
  if (attributes == NULL)
    {
      printf ("ERROR: can't allocate memory for fields attributes\n");
      return ENOMEM;
    }
  for (iter = 0; iter < count; iter++)
    {
      attributes[iter] = parse_attribute (loader, class);
    }
  *info = attributes;
  return 0;
}

int
parse_ConstantValue_at (Loader *loader, struct ConstantValue_attribute *attr)
{
  if (attr == NULL)
    {
      return EINVAL;
    }
  attr->constant_value_index = loader_u2 (loader);
  return 0;
}

int
parse_Code_attribute (Loader *loader, struct class_file *class,
                      struct Code_attribute *attr)
{
  int error = 0;
  uint32_t iter = 0;
  if (attr == NULL)
    {
      return EINVAL;
    }
  attr->max_stack = loader_u2 (loader);
  attr->max_locals = loader_u2 (loader);
  attr->code_length = loader_u4 (loader);
  attr->code = malloc (attr->code_length);
  if (attr->code == NULL)
    {
      return ENOMEM;
    }
  for (iter = 0; iter < attr->code_length; ++iter)
    {
      attr->code[iter] = loader_u1 (loader);
    }
  attr->exception_table_length = loader_u2 (loader);
  attr->table = malloc (sizeof (struct exception_table)
                        * attr->exception_table_length);
  if (attr->table == NULL)
    {
      free (attr->code);
      return ENOMEM;
    }
  for (iter = 0; iter < attr->exception_table_length; ++attr)
    {
      attr->table[iter].start_pc = loader_u2 (loader);
      attr->table[iter].end_pc = loader_u2 (loader);
      attr->table[iter].handler_pc = loader_u2 (loader);
      attr->table[iter].catch_type = loader_u2 (loader);
    }
  attr->attributes_count = loader_u2 (loader);
  error = read_attributes (loader, class, &attr->attributes,
                           attr->attributes_count);

  return error;
}

void
verification_type_parser (Loader *loader, union verification_type_info *stack)
{
  stack->tag = loader_u1 (loader);
  switch (stack->tag)
    {
    case 0: // ITEM_Top

    case 1: // ITEM_Integer

    case 2: // ITEM_Float

    case 3: // ITEM_Double

    case 4: // ITEM_Long

    case 5: // ITEM_Null

    case 6: // ITEM_UninitializedThis
      break;

    case 7: // ITEM_Object
      stack->Object_variable_info.cpool_index = loader_u2 (loader);
      break;

    case 8: // ITEM_Uninitialized
      stack->Uninitialized_variable_info.offset = loader_u2 (loader);
      break;

    default:
      printf ("ERROR: can not parse verification_type_parser\n");
      break;
    }
}

int
stack_map_frame_parser (Loader *loader, union stack_map_frame *entry)
{
  entry->frame_type = loader_u1 (loader);
  if (entry->frame_type <= 63)
    { // SAME FRAME
    }
  else if (entry->frame_type >= 64 && entry->frame_type <= 127)
    { // SAME_LOCALS_1_STACK_ITEM

      entry->same_locals_1_stack_item_frame.stack
          = malloc (sizeof (union verification_type_info));

      if (entry->same_locals_1_stack_item_frame.stack == NULL)
        {
          printf ("Error in malloc for "
                  "entry->same_locals_1_stack_item_frame.stack\n");
          return ENOMEM;
        }

      verification_type_parser (loader,
                                entry->same_locals_1_stack_item_frame.stack);
    }
  else if (entry->frame_type == 247)
    { // SAME_LOCALS_1_STACK_ITEM_EXTENDED

      entry->same_locals_1_stack_item_frame_extended.offset_delta
          = loader_u2 (loader);
      entry->same_locals_1_stack_item_frame_extended.stack
          = malloc (sizeof (union verification_type_info));

      if (entry->same_locals_1_stack_item_frame_extended.stack == NULL)
        {
          printf ("Error in malloc for "
                  "entry->same_locals_1_stack_item_frame_extended.stack\n");
          return ENOMEM;
        }

      verification_type_parser (
          loader, entry->same_locals_1_stack_item_frame_extended.stack);
    }
  else if (entry->frame_type >= 248 && entry->frame_type <= 250)
    { // CHOP

      entry->chop_frame.offset_delta = loader_u2 (loader);
    }
  else if (entry->frame_type == 250)
    { // SAME_FRAME_EXTENDED

      entry->same_frame_extended.offset_delta = loader_u2 (loader);
    }
  else if (entry->frame_type >= 252 && entry->frame_type <= 254)
    { // APPEND

      entry->append_frame.offset_delta = loader_u2 (loader);
      entry->append_frame.locals
          = malloc ((size_t)(entry->frame_type - 251)
                    * sizeof (union verification_type_info));

      if (entry->append_frame.locals == NULL)
        {
          printf ("Can not allocate memory for entry->append_frame.locals\n");
          return ENOMEM;
        }

      for (int i = 0; i < (entry->frame_type - 251); i++)
        {
          verification_type_parser (loader, &entry->append_frame.locals[i]);
        }
    }
  else if (entry->frame_type == 255)
    { // FULL_FRAME
      uint16_t iter;

      entry->full_frame.offset_delta = loader_u2 (loader);
      entry->full_frame.number_of_locals = loader_u2 (loader);

      entry->full_frame.locals
          = malloc ((size_t)(entry->full_frame.number_of_locals)
                    * sizeof (union verification_type_info));

      if (entry->full_frame.locals == NULL)
        {
          printf ("Can not allocate memory for entry->full_frame.locals\n");
          return ENOMEM;
        }

      for (iter = 0; iter < (entry->full_frame.number_of_locals); iter++)
        {
          verification_type_parser (loader, &entry->full_frame.locals[iter]);
        }

      entry->full_frame.number_of_stack_items = loader_u2 (loader);
      entry->full_frame.stack
          = malloc ((size_t)(entry->full_frame.number_of_stack_items)
                    * sizeof (union verification_type_info));

      if (entry->full_frame.locals == NULL)
        {
          printf ("Can not allocate memory for "
                  "entry->full_frame.number_of_stack_items\n");
          return ENOMEM;
        }

      for (iter = 0; iter < (entry->full_frame.number_of_stack_items); iter++)
        {
          verification_type_parser (loader, &entry->full_frame.stack[iter]);
        }
    }
  return 0;
}

int
parse_StackMapTable_at (Loader *loader, struct StackMapTable_attribute *attr)
{
  int error = 0;
  uint16_t iter = 0;

  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->number_of_entries = loader_u2 (loader);

  attr->entries
      = malloc ((sizeof (union stack_map_frame) * attr->number_of_entries));

  if (attr->entries == NULL)
    {
      printf ("Can not allocate memory in StackMapTable_at\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->number_of_entries; ++iter)
    {
      error = stack_map_frame_parser (loader, &attr->entries[iter]);
    }

  return error;
}

int
parse_bootstrap_methods (Loader *loader, struct bootstrap_methods *meth)
{
  uint16_t iter;
  meth->bootstrap_method_ref = loader_u2 (loader);
  meth->num_bootstrap_arguments = loader_u2 (loader);
  meth->bootstrap_arguments
      = malloc (sizeof (uint16_t) * (size_t)(meth->num_bootstrap_arguments));
  if (meth->bootstrap_arguments == NULL)
    {
      printf ("Can not allocate memory for bootstrap_arguments\n");
      return ENOMEM;
    }
  for (iter = 0; iter < meth->num_bootstrap_arguments; ++iter)
    {
      meth->bootstrap_arguments[iter] = loader_u2 (loader);
    }
  return 0;
}

int
parse_BootstrapMethods_at (Loader *loader,
                           struct BootstrapMethods_attribute *attr)
{
  uint16_t iter = 0;
  int error = 0;
  if (attr == NULL)
    {
      return EINVAL;
    }
  attr->num_bootstrap_methods = loader_u2 (loader);
  attr->bootstrap_methods = malloc ((size_t)(attr->num_bootstrap_methods)
                                    * sizeof (struct bootstrap_methods));

  if (attr->bootstrap_methods == NULL)
    {
      printf ("Can not allocate memory in BootstrapMethods_at\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->num_bootstrap_methods; ++iter)
    {
      error
          |= parse_bootstrap_methods (loader, &attr->bootstrap_methods[iter]);
    }

  if (error != 0)
    {
      printf ("Error in parsing Bootstrap_methods\n");
    }
  return error;
}

int
parse_NestHost_at (Loader *loader, struct NestHost_attribute *attr)
{
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->host_class_index = loader_u2 (loader);

  return 0;
}

int
parse_NestMembers_at (Loader *loader, struct NestMembers_attribute *attr)
{
  uint16_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->number_of_classes = loader_u2 (loader);
  attr->classes
      = malloc (sizeof (uint16_t) * (size_t)(attr->number_of_classes));

  if (attr->classes == NULL)
    {
      printf ("Can not allocate memory for attr->classes in NestMembers\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->number_of_classes; iter++)
    {
      attr->classes[iter] = loader_u2 (loader);
    }

  return 0;
}

int
parse_PermittedSubclasses_at (Loader *loader,
                              struct PermittedSubclasses_attribute *attr)
{
  uint16_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->number_of_classes = loader_u2 (loader);
  attr->classes
      = malloc (sizeof (uint16_t) * (size_t)(attr->number_of_classes));

  if (attr->classes == NULL)
    {
      printf ("Can not allocate memory for attr->classes in "
              "PermittedSubclasses\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->number_of_classes; iter++)
    {
      attr->classes[iter] = loader_u2 (loader);
    }

  return 0;
}

int
parse_Exceptions_at (Loader *loader, struct Exceptions_attribute *attr)
{
  uint16_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->number_of_exceptions = loader_u2 (loader);
  attr->exception_index_table
      = malloc (sizeof (uint16_t) * (size_t)(attr->number_of_exceptions));

  if (attr->exception_index_table == NULL)
    {
      printf (
          "Can not allocate memory for exception_index_table in Exceptions\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->number_of_exceptions; iter++)
    {
      attr->exception_index_table[iter] = loader_u2 (loader);
    }

  return 0;
}

int
parse_InnerClasses_at (Loader *loader, struct InnerClasses_attribute *attr)
{
  uint16_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->number_of_classes = loader_u2 (loader);
  attr->classes = malloc (sizeof (struct inner_class_entries)
                          * (size_t)(attr->number_of_classes));

  if (attr->classes == NULL)
    {
      printf ("Can not allocate memory for inner classes in InnerClasses\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->number_of_classes; ++iter)
    {
      attr->classes[iter].inner_class_info_index = loader_u2 (loader);
      attr->classes[iter].outer_class_info_index = loader_u2 (loader);
      attr->classes[iter].inner_name_index = loader_u2 (loader);
      attr->classes[iter].inner_class_access_flags = loader_u2 (loader);
    }

  return 0;
}

int
parse_EnclosingMethod_at (Loader *loader,
                          struct EnclosingMethod_attribute *attr)
{
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->class_index = loader_u2 (loader);
  attr->method_index = loader_u2 (loader);

  return 0;
}

int
parse_Synthetic_at (Loader *, struct Synthetic_attribute *attr)
{
  if (attr == NULL)
    {
      return EINVAL;
    }

  return 0;
}

int
parse_Signature_at (Loader *loader, struct Signature_attribute *attr)
{
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->signature_index = loader_u2 (loader);

  return 0;
}

int
parser_record_component_info (Loader *loader, struct class_file *class,
                              struct record_component_info *record)
{
  int error = 0;
  record->name_index = loader_u2 (loader);
  record->descriptor_index = loader_u2 (loader);
  record->attributes_count = loader_u2 (loader);

  error = read_attributes (loader, class, &record->attributes,
                           record->attributes_count);

  return error;
}

int
parse_Record_at (Loader *loader, struct class_file *class,
                 struct Record_attribute *attr)
{
  uint16_t iter;
  int error = 0;

  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->components_count = loader_u2 (loader);
  attr->components = malloc (sizeof (struct record_component_info)
                             * (size_t)(attr->components_count));

  if (attr->components == NULL)
    {
      printf ("Can not allocate memory for components in Record\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->components_count; iter++)
    {
      error |= parser_record_component_info (loader, class,
                                             &(attr->components[iter]));
    }

  if (error != 0)
    {
      printf ("ERROR: error in parsing record_component_info in Record\n");
    }

  return error;
}

int
parse_SourceFile_at (Loader *loader, struct SourceFile_attribute *attr)
{
  if (attr == NULL)
    {
      return EINVAL;
    }
  attr->sourcefile_index = loader_u2 (loader);
  return 0;
}

int
parse_LineNumberTable_at (Loader *loader,
                          struct LineNumberTable_attribute *attr)
{
  uint16_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }
  attr->line_number_table_length = loader_u2 (loader);
  attr->table = malloc (sizeof (struct line_number_table)
                        * attr->line_number_table_length);

  if (attr->table == NULL)
    {
      printf ("ERROR: Can not allocate memory for table in LineNumberTable\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->line_number_table_length; iter++)
    {
      attr->table[iter].start_pc = loader_u2 (loader);
      attr->table[iter].line_number = loader_u2 (loader);
    }

  return 0;
}

int
parse_LocalVariableTable_at (Loader *loader,
                             struct LocalVariableTable_attribute *attr)
{
  uint16_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->local_variable_table_length = loader_u2 (loader);
  attr->table = malloc (sizeof (struct local_variable_table)
                        * (size_t)(attr->local_variable_table_length));

  if (attr->table == NULL)
    {
      printf ("ERROR: Can not allocate memory for table in LineNumberTable\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->local_variable_table_length; iter++)
    {
      attr->table[iter].start_pc = loader_u2 (loader);
      attr->table[iter].length = loader_u2 (loader);
      attr->table[iter].name_index = loader_u2 (loader);
      attr->table[iter].descriptor_index = loader_u2 (loader);
      attr->table[iter].index = loader_u2 (loader);
    }

  return 0;
}

int
parse_LocalVariableTypeTable_at (Loader *loader,
                                 struct LocalVariableTypeTable_attribute *attr)
{
  uint16_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->local_variable_type_table_length = loader_u2 (loader);
  attr->table = malloc (sizeof (struct local_variable_type_table)
                        * (size_t)(attr->local_variable_type_table_length));
  if (attr->table == NULL)
    {
      printf ("ERROR: Can not allocate memory for table in "
              "LocalVariableTypeTable\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->local_variable_type_table_length; ++iter)
    {
      attr->table[iter].start_pc = loader_u2 (loader);
      attr->table[iter].length = loader_u2 (loader);
      attr->table[iter].name_index = loader_u2 (loader);
      attr->table[iter].signature_index = loader_u2 (loader);
      attr->table[iter].index = loader_u2 (loader);
    }

  return 0;
}

int
parse_SourceDebugExtension_at (Loader *loader,
                               struct SourceDebugExtension_attribute *attr)
{
  uint32_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->debug_extension
      = malloc (sizeof (uint8_t) * (size_t)(attr->info.attribute_length));
  if (attr->debug_extension == NULL)
    {
      printf ("ERROR: can not allocate memory for debug_extension in "
              "SourceDebugExtension\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->info.attribute_length; ++iter)
    {
      attr->debug_extension[iter] = loader_u1 (loader);
    }

  return 0;
}

int
parse_RuntimeVisibleAnnotations_at (
    Loader *, struct RuntimeVisibleAnnotations_attribute *)
{
  return -1;
}

// IT's ALL
int
parse_Deprecated_at (Loader *, struct Deprecated_attribute *attr)
{
  if (attr == NULL)
    {
      return EINVAL;
    }
  return 0;
}

int parse_annotations (Loader *loader, struct annotation *annotation);

int
parse_element_value (Loader *loader, struct element_value *elem)
{
  uint16_t iter = 0;
  elem->tag = loader_u1 (loader);
  switch (elem->tag)
    {
    case 'B':
    case 'C':
    case 'D':
    case 'F':
    case 'I':
    case 'J':
    case 'S':
    case 'Z':
    case 's':
      elem->value.const_value_index = loader_u2 (loader);
      break;

    case 'e':
      elem->value.enum_const_value.type_name_index = loader_u2 (loader);
      elem->value.enum_const_value.const_name_index = loader_u2 (loader);
      break;

    case 'c':
      elem->value.class_info_index = loader_u2 (loader);
      break;

    case '@':
      return parse_annotations (loader, &elem->value.annotation_value);
      break;

    case '[':
      elem->value.array_value.num_values = loader_u2 (loader);
      elem->value.array_value.values = malloc (
          sizeof (struct element_value) * elem->value.array_value.num_values);
      if (elem->value.array_value.values == NULL)
        {
          printf ("ERROR: can not allocate memory for element_value\n");
          return ENOMEM;
        }
      for (iter = 0; iter < elem->value.array_value.num_values; ++iter)
        {
          parse_element_value (loader, &elem->value.array_value.values[iter]);
        }
      break;

    default:
      printf ("ERROR: can not parse elem->tag\n");
      return EIO;
      break;
    }
  return 0;
}

int
parse_annotations (Loader *loader, struct annotation *annotation)
{
  uint16_t iter;
  annotation->type_index = loader_u2 (loader);
  annotation->num_element_value_pairs = loader_u2 (loader);
  for (iter = 0; iter < annotation->num_element_value_pairs; iter++)
    {
      annotation->element_value_pairs[iter].element_name_index
          = loader_u2 (loader);
      parse_element_value (loader,
                           &annotation->element_value_pairs[iter].value);
    }
  return 0;
}

int
parse_RuntimeInvisibleAnnotations_at (
    Loader *loader, struct RuntimeInvisibleAnnotations_attribute *attr)
{
  uint16_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->num_annotations = loader_u2 (loader);
  attr->annotations
      = malloc (sizeof (struct annotation) * (size_t)(attr->num_annotations));
  for (iter = 0; iter < attr->num_annotations; ++iter)
    {
      parse_annotations (loader, &attr->annotations[iter]);
    }
  return 0;
}

int
parse_RuntimeVisibleParameterAnnotations_at (
    Loader *loader, struct RuntimeVisibleParameterAnnotations_attribute *attr)
{
  uint8_t iter;

  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->num_parameters = loader_u1 (loader);
  attr->parameter_annotations = malloc (sizeof (struct parameter_annotations)
                                        * (size_t)(attr->num_parameters));

  if (attr->parameter_annotations == NULL)
    {
      printf ("ERROR: can not allocate memory for parameter annotations\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->num_parameters; ++iter)
    {
      attr->parameter_annotations[iter].num_annotations = loader_u2 (loader);
      attr->parameter_annotations[iter].annotations = malloc (
          sizeof (struct annotation)
          * (size_t)(attr->parameter_annotations[iter].num_annotations));

      if (attr->parameter_annotations[iter].annotations == NULL)
        {
          printf ("ERROR: can not allocate memory for annotations in "
                  "parameter annotations\n");
          return ENOMEM;
        }

      for (uint16_t i = 0;
           i < attr->parameter_annotations[iter].num_annotations; i++)
        {
          parse_annotations (
              loader, &attr->parameter_annotations[iter].annotations[i]);
        }
    }
  return 0;
}

int
parse_RuntimeInvisibleParameterAnnotations_at (
    Loader *loader,
    struct RuntimeInvisibleParameterAnnotations_attribute *attr)
{
  uint8_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->num_parameters = loader_u1 (loader);
  attr->parameter_annotations = malloc (sizeof (struct parameter_annotations)
                                        * (size_t)(attr->num_parameters));

  if (attr->parameter_annotations == NULL)
    {
      printf ("ERROR: can not allocate memory for parameter annotations\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->num_parameters; ++iter)
    {
      attr->parameter_annotations[iter].num_annotations = loader_u2 (loader);
      attr->parameter_annotations[iter].annotations = malloc (
          sizeof (struct annotation)
          * (size_t)(attr->parameter_annotations[iter].num_annotations));

      if (attr->parameter_annotations[iter].annotations == NULL)
        {
          printf ("ERROR: can not allocate memory for annotations in "
                  "parameter annotations\n");
          return ENOMEM;
        }

      for (uint16_t i = 0;
           i < attr->parameter_annotations[iter].num_annotations; i++)
        {
          parse_annotations (
              loader, &attr->parameter_annotations[iter].annotations[i]);
        }
    }
  return 0;
}

// TODO
int
parse_RuntimeVisibleTypeAnnotations_at (
    Loader *loader, struct RuntimeVisibleTypeAnnotations_attribute *attr)
{
  // uint16_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->num_annotations = loader_u2 (loader);
  attr->type_annotation = malloc (sizeof (struct type_annotation)
                                  * (size_t)(attr->num_annotations));

  if (attr->type_annotation == NULL)
    {
      printf ("ERROR: can not allocate memory for type_annotation in "
              "RuntimeVisibleTypeAnnotations\n");
      return ENOMEM;
    }

  return -1;
}

// TODO
int
parse_RuntimeInvisibleTypeAnnotations_at (
    Loader *, struct RuntimeInvisibleTypeAnnotations_attribute *attr)
{
  if (attr == NULL)
    {
      return EINVAL;
    }
  return 0;
}

// TODO
int
parse_AnnotationDefault_at (Loader *, struct AnnotationDefault_attribute *attr)
{
  if (attr == NULL)
    {
      return EINVAL;
    }
  return 0;
}

int
parse_MethodParameters_at (Loader *loader,
                           struct MethodParameters_attribute *attr)
{
  uint8_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }
  attr->parameters_count = loader_u1 (loader);
  attr->parameters = malloc (sizeof (struct method_params)
                             * (size_t)(attr->parameters_count));
  if (attr->parameters == NULL)
    {
      printf ("ERROR: can not allocate memory for parameters in "
              "MethodParameters\n");
      return ENOMEM;
    }
  for (iter = 0; iter < attr->parameters_count; ++iter)
    {
      attr->parameters[iter].name_index = loader_u2 (loader);
      attr->parameters[iter].access_flags = loader_u2 (loader);
    }

  return 0;
}

int
parse_module_exports (Loader *loader, struct exports *exports)
{
  uint16_t iter;
  exports->exports_index = loader_u2 (loader);
  exports->exports_flags = loader_u2 (loader);
  exports->exports_to_count = loader_u2 (loader);
  exports->exports_to_index
      = malloc (sizeof (uint16_t) * (size_t)(exports->exports_to_count));

  if (exports->exports_to_index == NULL)
    {
      printf (
          "ERROR: Can not allocate memory for exports_to_index in Module\n");
      return ENOMEM;
    }

  for (iter = 0; iter < exports->exports_to_count; ++iter)
    {
      exports->exports_to_index[iter] = loader_u2 (loader);
    }
  return 0;
}

int
parse_module_opens (Loader *loader, struct opens *opens)
{
  uint16_t iter;
  opens->opens_index = loader_u2 (loader);
  opens->opens_flags = loader_u2 (loader);
  opens->opens_to_count = loader_u2 (loader);
  opens->opens_to_index
      = malloc (sizeof (uint16_t) * (size_t)(opens->opens_to_count));

  if (opens->opens_to_index == NULL)
    {
      printf ("ERROR: Can not allocate memory for opens_to_index in Module\n");
      return ENOMEM;
    }

  for (iter = 0; iter < opens->opens_to_count; ++iter)
    {
      opens->opens_to_index[iter] = loader_u2 (loader);
    }
  return 0;
}

int
parse_module_provides (Loader *loader, struct provides *provides)
{
  uint16_t iter;
  provides->provides_index = loader_u2 (loader);
  provides->provides_with_count = loader_u2 (loader);
  provides->provides_with_index
      = malloc (sizeof (uint16_t) * (size_t)(provides->provides_with_count));

  if (provides->provides_with_index == NULL)
    {
      printf ("ERROR: Can not allocate memory for provides_with_index in "
              "Module\n");
      return ENOMEM;
    }

  for (iter = 0; iter < provides->provides_with_count; ++iter)
    {
      provides->provides_with_index[iter] = loader_u2 (loader);
    }
  return 0;
}

// TODO
int
parse_Module_at (Loader *loader, struct Module_attribute *attr)
{
  uint16_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }
  attr->module_name_index = loader_u2 (loader);
  attr->module_flags = loader_u2 (loader);
  attr->module_version_index = loader_u2 (loader);

  attr->requires_count = loader_u2 (loader);
  attr->requires
      = malloc (sizeof (struct requires) * (size_t)(attr->requires_count));

  if (attr->requires == NULL)
    {
      printf ("ERROR: can not allocate memory for requires in Module\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->requires_count; ++iter)
    {
      attr->requires[iter].requires_index = loader_u2 (loader);
      attr->requires[iter].requires_flags = loader_u2 (loader);
      attr->requires[iter].requires_version_index = loader_u2 (loader);
    }

  attr->exports_count = loader_u2 (loader);
  attr->exports
      = malloc (sizeof (struct exports) * (size_t)(attr->exports_count));

  if (attr->exports == NULL)
    {
      printf ("ERROR: can not allocate memory for exports in Module\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->exports_count; ++iter)
    {
      parse_module_exports (loader, attr->exports);
    }

  attr->opens_count = loader_u2 (loader);
  attr->opens = malloc (sizeof (struct opens) * (size_t)(attr->opens_count));
  if (attr->opens == NULL)
    {
      printf ("ERROR: can not allocate memory for opens in Module\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->opens_count; ++iter)
    {
      parse_module_opens (loader, attr->opens);
    }

  attr->uses_count = loader_u2 (loader);
  attr->uses_index
      = malloc (sizeof (attr->uses_index) * (size_t)(attr->uses_count));

  if (attr->uses_index == NULL)
    {
      printf ("ERROR: Can not allocate memory for uses index in Module\n");
      return ENOMEM;
    }

  for (iter = 0; iter < attr->uses_count; iter++)
    {
      attr->uses_index[iter] = loader_u2 (loader);
    }

  attr->provides_count = loader_u2 (loader);
  attr->provides
      = malloc (sizeof (struct provides) * (size_t)(attr->provides_count));

  for (iter = 0; iter < attr->provides_count; iter++)
    {
      parse_module_provides (loader, attr->provides);
    }

  return 0;
}

int
parse_ModulePackages_at (Loader *loader, struct ModulePackages_attribute *attr)
{
  uint16_t iter;
  if (attr == NULL)
    {
      return EINVAL;
    }
  attr->package_count = loader_u2 (loader);
  attr->package_index
      = malloc (sizeof (uint16_t) * (size_t)(attr->package_count));
  for (iter = 0; iter < attr->package_count; ++iter)
    {
      attr->package_index[iter] = loader_u2 (loader);
    }

  return 0;
}

int
parse_ModuleMainClass_at (Loader *loader,
                          struct ModuleMainClass_attribute *attr)
{
  if (attr == NULL)
    {
      return EINVAL;
    }

  attr->main_class_index = loader_u2 (loader);
  return 0;
}