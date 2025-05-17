#include "rt_attr_parser.h"

#define PARSE_ATTRIBUTE_BASE(TYPE, NAME, LENGTH)                              \
  TYPE *attr = my_alloc (TYPE);                                               \
  if (attr == NULL)                                                           \
    {                                                                         \
      prerr ("Cannot allocate memory for attribute %s", NAME);                \
      return -1;                                                              \
    }                                                                         \
  attr->header.name = NAME;                                                   \
  attr->header.attribute_length = LENGTH

#define CHECK_ERROR_AND_SET(err, msg, new_attribute, attribute)               \
  do                                                                          \
    {                                                                         \
      if (err)                                                                \
        {                                                                     \
          prerr ("Parse %s failed", msg);                                     \
          if (new_attribute)                                                  \
            *new_attribute = NULL;                                            \
          return -1;                                                          \
        }                                                                     \
      if (new_attribute)                                                      \
        *new_attribute = (struct rt_attribute *)attribute;                    \
    }                                                                         \
  while (0)

// ---- InnerClasses attribute ----

int
parse_rt_innerClasses_attribute (struct runtime_cp *rt_cp,
                                 struct rt_innerClasses_attribute *attr,
                                 struct InnerClasses_attribute *old_attr,
                                 uint16_t runtime_cp_count)
{
  int err;
  uint16_t iter;
  attr->number_of_classes = old_attr->number_of_classes;
  attr->classes = my_alloc_array (struct rt_inner_class_entries,
                                  attr->number_of_classes);

  for (iter = 0; iter < attr->number_of_classes; ++iter)
    {
      err |= parse_rt_classname (
          rt_cp, &attr->classes[iter].inner_class,
          old_attr->classes[iter].inner_class_info_index, runtime_cp_count);
      // if not member
      if (old_attr->classes[iter].outer_class_info_index == 0)
        {
          attr->classes[iter].outer_class = "NONE";
        }
      else
        {
          err |= parse_rt_classname (
              rt_cp, &attr->classes[iter].outer_class,
              old_attr->classes[iter].outer_class_info_index,
              runtime_cp_count);
        }
      // if anonymous
      if (old_attr->classes[iter].inner_name_index == 0)
        {
          attr->classes[iter].inner_name = "NONE";
        }
      else
        {
          err |= parse_rt_index_to_string (
              rt_cp, &attr->classes[iter].inner_name,
              old_attr->classes[iter].inner_name_index, runtime_cp_count);
        }
      if (err)
        {
          prerr ("Can not parse innerClasses");
          return -1;
        }
      attr->classes[iter].inner_class_access_flags
          = old_attr->classes[iter].inner_class_access_flags;
      printf ("  inner_cl: %s, outer_cl: %s, inner_name: %s\n",
              attr->classes[iter].inner_class, attr->classes[iter].outer_class,
              attr->classes[iter].inner_name);
    }
  return 0;
}

// ---- SourceFile attribute ----

int
parse_rt_sourceFile_attribute (struct runtime_cp *rt_cp,
                               struct rt_sourceFile_attribute *attr,
                               struct SourceFile_attribute *old_attr,
                               uint16_t runtime_cp_count)
{
  int err = parse_rt_index_to_string (
      rt_cp, &attr->sourcefile, old_attr->sourcefile_index, runtime_cp_count);
  if (err)
    {
      printf ("Can not parse SourceFile");
      return -1;
    }
  printf ("   source file - %s\n", attr->sourcefile);
  return 0;
}

// ---- Signature attribute ----

int
parse_rt_signature_attribute (struct runtime_cp *rt_cp,
                              struct rt_signature_attribute *attr,
                              struct Signature_attribute *old_attr,
                              uint16_t runtime_cp_count)
{
  int err = parse_rt_index_to_string (
      rt_cp, &attr->signature, old_attr->signature_index, runtime_cp_count);

  if (err)
    {
      prerr ("Can not parse utf8 in Signature");
      return -1;
    }

  printf ("  signature: %s\n", attr->signature);

  return 0;
}

// ---- StackMapTable attribute ----

int
parse_rt_verification_type_info (struct runtime_cp *rt_cp,
                                 union rt_verification_type_info *type,
                                 union verification_type_info *old_type,
                                 uint16_t runtime_cp_count)
{
  type->tag = old_type->tag;
  printf (" tag - ");
  int err;
  switch (type->tag)
    {
    case 0: // ITEM_Top
      printf (" ITEM_Top\n");
      break;
    case 1: // ITEM_Integer
      printf (" ITEM_Integer\n");
      break;
    case 2: // ITEM_Float
      printf (" ITEM_Float\n");
      break;
    case 3: // ITEM_Double
      printf (" ITEM_Double\n");
      break;
    case 4: // ITEM_Long
      printf (" ITEM_Long\n");
      break;
    case 5: // ITEM_Null
      printf (" ITEM_Null\n");
      break;
    case 6: // ITEM_UninitializedThis
      printf (" ITEM_UninitializedThis\n");
      break;

    case 7: // ITEM_Object
      printf (" ITEM_Object, ");
      err = parse_rt_classname (rt_cp, &type->Object_variable_info.cpool,
                                old_type->Object_variable_info.cpool_index,
                                runtime_cp_count);
      if (err)
        {
          prerr ("Can not parse ITEM_OBJECT");
          return -1;
        }
      printf ("class - %s\n", type->Object_variable_info.cpool);
      break;

    case 8: // ITEM_Uninitialized
      printf (" ITEM_Uninitialized, ");
      type->Uninitialized_variable_info.offset
          = old_type->Uninitialized_variable_info.offset;
      printf ("offset - %hu\n", type->Uninitialized_variable_info.offset);
      break;

    default:
      prerr ("Can not parse verification_type_parser");
      return -1;
      break;
    }
  return 0;
}

int
parse_rt_stack_map_frame (struct runtime_cp *rt_cp,
                          union rt_stack_map_frame *frame,
                          union stack_map_frame *old_frame,
                          uint16_t runtime_cp_count)
{
  uint8_t frame_type = old_frame->frame_type;
  int err = 0;
  frame->frame_type = frame_type;
  printf ("  frame type - %-3hhu\n", frame_type);

  if (frame_type <= 63)
    {
    }
  else if (frame_type <= 127)
    {
      union rt_verification_type_info *stack
          = my_alloc (union rt_verification_type_info);
      if (stack == NULL)
        {
          prerr ("Can not allocate memory for same_locals_1_stack_item_frame");
          return ENOMEM;
        }
      err = parse_rt_verification_type_info (
          rt_cp, stack, old_frame->same_locals_1_stack_item_frame.stack,
          runtime_cp_count);

      if (err)
        {
          prerr ("Can not parse rt_verification_type_info in "
                 "same_locals_1_stack_item_frame");
          return -1;
        }

      frame->same_locals_1_stack_item_frame.stack = stack;
    }
  else if (frame_type == 247)
    // SAME_LOCALS_1_STACK_ITEM_EXTENDED
    {
      frame->same_locals_1_stack_item_frame_extended.offset_delta
          = old_frame->same_locals_1_stack_item_frame_extended.offset_delta;
      union rt_verification_type_info *stack
          = my_alloc (union rt_verification_type_info);
      if (stack == NULL)
        {
          prerr (
              "Can not allocate memory for SAME_LOCALS_1_STACK_ITEM_EXTENDED");
          return ENOMEM;
        }
      err = parse_rt_verification_type_info (
          rt_cp, stack, old_frame->same_locals_1_stack_item_frame.stack,
          runtime_cp_count);

      if (err)
        {
          prerr ("Can not parse rt_verification_type_info in "
                 "SAME_LOCALS_1_STACK_ITEM_EXTENDED");
          return -1;
        }

      frame->same_locals_1_stack_item_frame.stack = stack;
    }
  else if (frame_type >= 248 && frame_type <= 250)
    { // CHOP

      frame->chop_frame.offset_delta = old_frame->chop_frame.offset_delta;
    }
  else if (frame_type == 251)
    { // SAME_FRAME_EXTENDED

      frame->same_frame_extended.offset_delta
          = old_frame->same_frame_extended.offset_delta;
    }
  else if (frame_type >= 252 && frame_type <= 254)
    { // APPEND

      frame->append_frame.offset_delta = old_frame->append_frame.offset_delta;
      frame->append_frame.locals = my_alloc_array (
          union rt_verification_type_info, (frame_type - 251));

      if (frame->append_frame.locals == NULL)
        {
          prerr ("Can not allocate memory for entry->append_frame.locals");
          return ENOMEM;
        }

      for (int i = 0; i < (frame_type - 251); i++)
        {
          err |= parse_rt_verification_type_info (
              rt_cp, &frame->append_frame.locals[i],
              &old_frame->append_frame.locals[i], runtime_cp_count);
        }
      if (err)
        {
          prerr (
              "Error while parsing rt_verification_type_info in append frame");
          return -1;
        }
    }
  else if (frame_type == 255)
    { // FULL_FRAME
      uint16_t iter;

      frame->full_frame.offset_delta = old_frame->full_frame.offset_delta;
      frame->full_frame.number_of_locals
          = old_frame->full_frame.number_of_locals;

      frame->full_frame.locals = my_alloc_array (
          union rt_verification_type_info, frame->full_frame.number_of_locals);

      if (frame->full_frame.locals == NULL)
        {
          prerr ("Can not allocate memory for entry->full_frame.locals");
          return ENOMEM;
        }

      for (iter = 0; iter < (frame->full_frame.number_of_locals); iter++)
        {
          err |= parse_rt_verification_type_info (
              rt_cp, &frame->full_frame.locals[iter],
              &old_frame->full_frame.locals[iter], runtime_cp_count);
        }

      if (err)
        {
          prerr ("Can not parse rt_verification_type_info for locals in full "
                 "frame");
          return -1;
        }

      frame->full_frame.number_of_stack_items
          = old_frame->full_frame.number_of_stack_items;
      frame->full_frame.stack
          = my_alloc_array (union rt_verification_type_info,
                            frame->full_frame.number_of_stack_items);

      if (frame->full_frame.stack == NULL)
        {
          prerr ("Can not allocate memory for "
                 "entry->full_frame.stack");
          return ENOMEM;
        }

      for (iter = 0; iter < (frame->full_frame.number_of_stack_items); iter++)
        {
          err |= parse_rt_verification_type_info (
              rt_cp, &frame->full_frame.stack[iter],
              &old_frame->full_frame.stack[iter], runtime_cp_count);
        }

      if (err)
        {
          prerr ("Can not parse rt_verification_type_info for stack in full "
                 "frame");
          return -1;
        }
    }
  printf ("\n");
  return 0;
}

int
parse_rt_stackMapTable_attribute (struct runtime_cp *rt_cp,
                                  struct rt_stackMapTable_attribute *attr,
                                  struct StackMapTable_attribute *old_attr,
                                  uint16_t runtime_cp_count)
{
  uint16_t iter;
  int err;
  attr->number_of_entries = old_attr->number_of_entries;
  attr->entries
      = my_alloc_array (union rt_stack_map_frame, attr->number_of_entries);
  if (attr->entries == NULL)
    {
      prerr ("Can not allocate memory for union rt_stack_map_frame");
      return ENOMEM;
    }
  for (iter = 0; iter < attr->number_of_entries; ++iter)
    {
      err = parse_rt_stack_map_frame (rt_cp, &attr->entries[iter],
                                      &old_attr->entries[iter],
                                      runtime_cp_count);
    }
  if (err)
    {
      prerr ("Can not parse rt_stackMapTable_attribute");
      return -1;
    }
  return 0;
}

// ---- Exceptions attribute ----

int
parse_rt_exceptions_attribute (struct runtime_cp *rt_cp,
                               struct rt_exceptions_attribute *attr,
                               struct Exceptions_attribute *old_attr,
                               uint16_t runtime_cp_count)
{
  uint16_t iter;
  int err;
  attr->number_of_exceptions = old_attr->number_of_exceptions;
  attr->exception_table = my_alloc_array (string, attr->number_of_exceptions);
  if (attr->exception_table == NULL)
    {
      prerr ("Can not allocate memory for exception table in Exceptions");
      return ENOMEM;
    }

  printf ("Exceptions: \n");

  for (iter = 0; iter < attr->number_of_exceptions; ++iter)
    {
      err = parse_rt_classname (rt_cp, &attr->exception_table[iter],
                                old_attr->exception_index_table[iter],
                                runtime_cp_count);

      if (err)
        {
          prerr ("Can not parse classes in Exceptions");
          return -1;
        }

      printf ("   #%-3hu: %s\n", iter, attr->exception_table[iter]);
    }

  return 0;
}

// ---- NestMembers attribute ----

int
parse_rt_nestMembers_attribute (struct runtime_cp *rt_cp,
                                struct rt_nestMembers_attribute *attr,
                                struct NestMembers_attribute *old_attr,
                                uint16_t runtime_cp_count)
{
  uint16_t iter;
  int err;
  attr->number_of_classes = old_attr->number_of_classes;
  attr->classes = my_alloc_array (string, attr->number_of_classes);
  if (attr->classes == NULL)
    {
      prerr ("Can not allocate memory for classes in nest members");
      return ENOMEM;
    }

  printf ("NestMembers: \n");

  for (iter = 0; iter < attr->number_of_classes; ++iter)
    {
      err = parse_rt_classname (rt_cp, &attr->classes[iter],
                                old_attr->classes[iter], runtime_cp_count);
      if (err)
        {
          prerr ("Can not parse classes in NestMembers");
          return -1;
        }

      printf ("   #-3hu: %s", attr->classes[iter]);
    }

  return 0;
}

// ---- LineNumberTable attribute ----

int
parse_rt_lineNumberTable_attribute (struct runtime_cp *,
                                    struct rt_lineNumberTable_attribute *attr,
                                    struct LineNumberTable_attribute *old_attr,
                                    uint16_t)
{
  uint16_t iter;
  attr->line_number_table_length = old_attr->line_number_table_length;
  attr->table = my_alloc_array (struct rt_line_number_table,
                                attr->line_number_table_length);
  if (attr->table == NULL)
    {
      prerr ("can not allocate memory for rt_line_number_table");
      return -1;
    }

  for (iter = 0; iter < attr->line_number_table_length; ++iter)
    {
      attr->table[iter].start_pc = old_attr->table[iter].start_pc;
      attr->table[iter].line_number = old_attr->table[iter].line_number;
      printf ("   line %-4hu: %-4hu\n", attr->table[iter].line_number,
              attr->table[iter].start_pc);
    }
  return 0;
}

// ---- CODE ATTRIBUTE ----

int
parse_exception_table (struct runtime_cp *rt_cp,
                       struct rt_exception_table **rt_table,
                       struct exception_table *old_table,
                       uint16_t exception_table_length,
                       uint16_t runtime_cp_count)
{
  uint16_t iter;
  int err;
  if (exception_table_length == 0)
    {
      return 0;
    }
  struct rt_exception_table *new_table
      = my_alloc_array (struct rt_exception_table, exception_table_length);
  if (new_table == NULL)
    {
      prerr ("can not allocate memory for rt_exception_table");
      return ENOMEM;
    }

  printf ("RT_EXCEPTION_TABLE:\n");
  for (iter = 0; iter < exception_table_length; ++iter)
    {
      printf ("  #%-3u: \n", iter);
      new_table[iter].start_pc = old_table[iter].start_pc;
      new_table[iter].end_pc = old_table[iter].end_pc;
      new_table[iter].handler_pc = old_table[iter].catch_type;
      if (old_table[iter].catch_type == 0)
        {
          new_table[iter].catch_type = "ALL";
        }
      else
        {
          err = parse_rt_classname (rt_cp, &new_table[iter].catch_type,
                                    old_table[iter].catch_type,
                                    runtime_cp_count);
          if (err)
            {
              prerr ("can not parse catch type of exception");
              return -1;
            }
        }
      printf ("  start_pc   - %-3hu\n", new_table[iter].start_pc);
      printf ("  end_pc     - %-3hu\n", new_table[iter].end_pc);
      printf ("  handler_pc - %-3hu\n", new_table[iter].handler_pc);
      printf ("  catch_type - %s\n", new_table[iter].catch_type);
    }
  *rt_table = new_table;
  return 0;
}

int
parse_rt_code_attribute (struct runtime_cp *rt_cp,
                         struct rt_code_attribute *attr,
                         struct Code_attribute *old_attr,
                         uint16_t runtime_cp_count)
{
  uint32_t code_iter;
  int err;
  attr->max_stack = old_attr->max_stack;
  attr->max_locals = old_attr->max_locals;
  attr->code_length = old_attr->code_length;
  attr->code = my_alloc_array (struct runtime_opcode, attr->code_length);

  if (attr->code == NULL)
    {
      prerr ("can not allocate memory for code");
      return ENOMEM;
    }

  for (code_iter = 0; code_iter < attr->code_length; ++code_iter)
    {
      uint8_t opcode = old_attr->code[code_iter];
      if (OPCODE_TABLE[opcode].handler)
        {
          attr->code[code_iter] = OPCODE_TABLE[opcode];
          printf ("   #%-3u - %s\n", code_iter, attr->code[code_iter].name);
        }
      else
        {
          attr->code[code_iter] = (struct runtime_opcode){
            .name = "UNKNOWN", .handler = opcode_error, .raw_byte = opcode
          };
        }
    }

  // start convert exception table

  attr->exception_table_length = old_attr->exception_table_length;
  err = parse_exception_table (rt_cp, &attr->table, old_attr->table,
                               attr->exception_table_length, runtime_cp_count);
  if (err)
    {
      prerr ("Can not parse exception table");
      return -1;
    }

  // start convert inner attributes

  attr->attributes_count = old_attr->attributes_count;
  err = parse_rt_attributes (rt_cp, &attr->attributes, old_attr->attributes,
                             attr->attributes_count, runtime_cp_count);
  if (err)
    {
      prerr ("Can not parse inner attributes in Code attr");
      return -1;
    }

  return 0;
}

// ---- ConstantValue Attribute ----

int
parse_rt_constantValue_attribute (struct runtime_cp *rt_cp,
                                  struct rt_constantValue_attribute *attr,
                                  struct ConstantValue_attribute *old_attr,
                                  uint16_t runtime_cp_count)
{
  if (!rt_cp || !attr || !old_attr)
    return EINVAL;

  uint16_t index = old_attr->constant_value_index;
  if (index == 0 || index > runtime_cp_count)
    return JVM_INVALID_BYTECODE;

  struct runtime_cp *entry = &rt_cp[index - 1];

  jvariable val = {0};

  switch (entry->tag)
    {
    case INTEGER:
      val.type = JINT;
      val.value._int = entry->integer_info;
      break;

    case FLOAT:
      val.type = JFLOAT;
      val.value._float = entry->float_info;
      break;

    case LONG:
      val.type = JLONG;
      val.value._long = entry->long_info;
      break;

    case DOUBLE:
      val.type = JDOUBLE;
      val.value._double = entry->double_info;
      break;

    case STRING:
      if (entry->string_info == NULL)
        {
          prerr ("ConstantValue: string_object is NULL at cp[%d]", index);
          return JVM_NULL_POINTER;
        }
      // val.type = JOBJECT;
      // val.value._object = entry->string_object;
      break;

    default:
      prerr ("ConstantValue: invalid CP tag=%d at index=%d", entry->tag, index);
      return JVM_INVALID_BYTECODE;
    }

  attr->constant_value = val;

  return 0;
}


// ---- PARSE ATTRIBUTES ----

int
parse_single_rt_attr (struct runtime_cp *rt_cp,
                      struct rt_attribute **new_attribute,
                      struct attribute_info *old_attribute,
                      uint16_t runtime_cp_count)
{
  int err = 0;
  string name = 0;
  err = parse_rt_index_to_string (
      rt_cp, &name, old_attribute->attribute_name_index, runtime_cp_count);
  uint16_t attribute_length = old_attribute->attribute_length;

  if (err)
    {
      prerr ("Can not read attr name");
      return err;
    }
  printf ("Attribute name : %s\n", name);
  if (strcmp (name, "ConstantValue") == 0)
    // start converting Code
    {
      PARSE_ATTRIBUTE_BASE (struct rt_constantValue_attribute, name,
                            attribute_length);
      attr->header.type = ATTRIBUTE_ConstantValue;

      struct ConstantValue_attribute *original_attr
          = (struct ConstantValue_attribute *)old_attribute;
      err = parse_rt_constantValue_attribute (rt_cp, attr, original_attr,
                                              runtime_cp_count);

      CHECK_ERROR_AND_SET (err, name, new_attribute, attr);
    }
  else if (strcmp (name, "Code") == 0)
    // start converting Code
    {
      PARSE_ATTRIBUTE_BASE (struct rt_code_attribute, name, attribute_length);
      attr->header.type = ATTRIBUTE_Code;

      struct Code_attribute *original_attr
          = (struct Code_attribute *)old_attribute;
      err = parse_rt_code_attribute (rt_cp, attr, original_attr,
                                     runtime_cp_count);

      CHECK_ERROR_AND_SET (err, name, new_attribute, attr);
    }
  else if (strcmp (name, "LineNumberTable") == 0)
    // start converting LineNumberTable
    {
      PARSE_ATTRIBUTE_BASE (struct rt_lineNumberTable_attribute, name,
                            attribute_length);
      attr->header.type = ATTRIBUTE_LineNumberTable;

      struct LineNumberTable_attribute *original_attr
          = (struct LineNumberTable_attribute *)old_attribute;
      err = parse_rt_lineNumberTable_attribute (rt_cp, attr, original_attr,
                                                runtime_cp_count);
      CHECK_ERROR_AND_SET (err, name, new_attribute, attr);
    }
  else if (strcmp (name, "StackMapTable") == 0)
    // start converting StackMapTable
    {
      PARSE_ATTRIBUTE_BASE (struct rt_stackMapTable_attribute, name,
                            attribute_length);
      attr->header.type = ATTRIBUTE_StackMapTable;

      struct StackMapTable_attribute *original_attr
          = (struct StackMapTable_attribute *)old_attribute;
      err = parse_rt_stackMapTable_attribute (rt_cp, attr, original_attr,
                                              runtime_cp_count);
      CHECK_ERROR_AND_SET (err, name, new_attribute, attr);
    }
  else if (strcmp (name, "NestMembers") == 0)
    // start converting NestMembers
    {
      PARSE_ATTRIBUTE_BASE (struct rt_nestMembers_attribute, name,
                            attribute_length);
      attr->header.type = ATTRIBUTE_NestHost;

      struct NestMembers_attribute *original_attr
          = (struct NestMembers_attribute *)old_attribute;
      err = parse_rt_nestMembers_attribute (rt_cp, attr, original_attr,
                                            runtime_cp_count);
      CHECK_ERROR_AND_SET (err, name, new_attribute, attr);
    }
  else if (strcmp (name, "Exceptions") == 0)
    // start converting Exceptions
    {
      PARSE_ATTRIBUTE_BASE (struct rt_exceptions_attribute, name,
                            attribute_length);
      attr->header.type = ATTRIBUTE_Exceptions;

      struct Exceptions_attribute *original_attr
          = (struct Exceptions_attribute *)old_attribute;
      err = parse_rt_exceptions_attribute (rt_cp, attr, original_attr,
                                           runtime_cp_count);
      CHECK_ERROR_AND_SET (err, name, new_attribute, attr);
    }
  else if (strcmp (name, "Signature") == 0)
    // start converting Signature
    {
      PARSE_ATTRIBUTE_BASE (struct rt_signature_attribute, name,
                            attribute_length);
      attr->header.type = ATTRIBUTE_Signature;

      struct Signature_attribute *original_attr
          = (struct Signature_attribute *)old_attribute;
      err = parse_rt_signature_attribute (rt_cp, attr, original_attr,
                                          runtime_cp_count);
      CHECK_ERROR_AND_SET (err, name, new_attribute, attr);
    }
  else if (strcmp (name, "InnerClasses") == 0)
    // start converting InnerClasses
    {
      PARSE_ATTRIBUTE_BASE (struct rt_innerClasses_attribute, name,
                            attribute_length);
      attr->header.type = ATTRIBUTE_InnerClasses;

      struct InnerClasses_attribute *original_attr
          = (struct InnerClasses_attribute *)old_attribute;
      err = parse_rt_innerClasses_attribute (rt_cp, attr, original_attr,
                                             runtime_cp_count);
      CHECK_ERROR_AND_SET (err, name, new_attribute, attr);
    }
  else if (strcmp (name, "SourceFile") == 0)
    // start converting SourceFile
    {
      PARSE_ATTRIBUTE_BASE (struct rt_sourceFile_attribute, name,
                            attribute_length);
      attr->header.type = ATTRIBUTE_SourceFile;

      struct SourceFile_attribute *original_attr
          = (struct SourceFile_attribute *)old_attribute;
      err = parse_rt_sourceFile_attribute (rt_cp, attr, original_attr,
                                           runtime_cp_count);
      CHECK_ERROR_AND_SET (err, name, new_attribute, attr);
    }
  else
    {
      prerr ("Attribute %s is not supported", name);
      return -1;
    }
  return 0;
}

int
parse_rt_attributes (struct runtime_cp *rt_cp,
                     struct rt_attribute ***attributes,
                     struct attribute_info **old_attributes,
                     uint16_t attributes_count, uint16_t runtime_cp_count)
{
  uint16_t iter;
  int err = 0;
  struct rt_attribute **new_attributes
      = my_alloc_array (struct rt_attribute *, attributes_count);
  if (new_attributes == NULL)
    {
      prerr ("can not allocate memory for rt attr");
      return ENOMEM;
    }
  for (iter = 0; iter < attributes_count; iter++)
    {
      err |= parse_single_rt_attr (rt_cp, &new_attributes[iter],
                                   old_attributes[iter], runtime_cp_count);
      if (err)
        {
          prerr ("can not parse attribute %hu", iter);
          return -1;
        }
    }

  *attributes = new_attributes;
  return 0;
}

struct rt_attribute *
find_attribute (struct rt_attribute **attributes, uint16_t attributes_count,
                attr_type type)
{
  uint16_t iter;
  for (iter = 0; iter < attributes_count; ++iter)
    {
      if (attributes[iter]->type == type)
        {
          return attributes[iter];
        }
    }
  return NULL;
}