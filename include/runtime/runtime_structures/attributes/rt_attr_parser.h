#ifndef SHIP_JVM_RT_ATTR_PARSER_H
#define SHIP_JVM_RT_ATTR_PARSER_H

#include "attribute_info.h"
#include "runtime_attribute.h"
#include "runtime_constpool.h"
#include "bytecodes.h"

int parse_single_rt_attr (struct runtime_cp *rt_cp,
                          struct rt_attribute **attribute,
                          struct attribute_info *old_attribute,
                          uint16_t runtime_cp_count);

int parse_rt_attributes (struct runtime_cp *rt_cp,
                         struct rt_attribute ***attributes,
                         struct attribute_info **old_attributes,
                         uint16_t attributes_count, uint16_t runtime_cp_count);

#endif