#include "rt_attr_parser.h"

#define PARSE_ATTRIBUTE_BASE(TYPE, NAME, LENGTH) \
    TYPE *attr = my_alloc(TYPE);            \
    if (attr == NULL) {                          \
        prerr("Cannot allocate memory for attribute %s", NAME); \
        return -1;                               \
    }                                           \
    attr->header.name = NAME;                   \
    attr->header.attribute_length = LENGTH

#define CHECK_ERROR_AND_SET(err, msg, new_attribute, attribute) \
    do { \
        if (err) { \
            prerr("Parse %s failed", msg); \
            if (new_attribute) *new_attribute = NULL; \
            return -1; \
        } \
        if (new_attribute) *new_attribute = (struct rt_attribute *) attribute; \
    } while (0)

int parse_rt_code_attribute(struct runtime_cp *, struct rt_code_attribute* attr, struct Code_attribute* old_attr, uint16_t )
{
  uint32_t code_iter;
  attr->max_stack = old_attr->max_stack;
  attr->max_locals = old_attr->max_locals;
  attr->code_length = old_attr->code_length;
  attr->code = my_alloc_array(struct runtime_opcode, attr->code_length);

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
      printf("Opcode - %s", attr->code[code_iter].name);
    }
    else
    {
      attr->code[code_iter] = (struct runtime_opcode){
        .name = "UNKNOWN",
        .handler = NULL
      };
      prerr ("Can not parse opcode %hhu", opcode);
      return -1;
    }
  }

  return 0;


}


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
  if (strcmp(name, "Code"))
  {
    PARSE_ATTRIBUTE_BASE(struct rt_code_attribute, name, attribute_length);
    struct Code_attribute* original_attr = (struct Code_attribute*) old_attribute;
    err = parse_rt_code_attribute(rt_cp, attr, original_attr, runtime_cp_count);

    CHECK_ERROR_AND_SET(err, name, new_attribute, attr);
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
      printf ("Iteration %hu :", iter);
      err |= parse_single_rt_attr (rt_cp, &new_attributes[iter],
                                   old_attributes[iter], runtime_cp_count);
    }

  *attributes = new_attributes;
  return 0;
}