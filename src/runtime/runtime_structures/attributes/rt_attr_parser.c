#include "rt_attr_parser.h"

// todo
int
parse_single_rt_attr (struct runtime_cp *rt_cp,
                      struct rt_attribute **attribute,
                      struct attribute_info *old_attribute,
                      uint16_t runtime_cp_count)
{
  int err = 0;
  string name = 0;
  err = parse_rt_index_to_string (
      rt_cp, &name, old_attribute->attribute_name_index, runtime_cp_count);

  if (err)
    {
      prerr ("Can not read attr name");
      return err;
    }
  printf ("attr name : %s\n", name);
  if (*attribute)
    {
      ;
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