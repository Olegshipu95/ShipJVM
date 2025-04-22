#ifndef SHIP_JVM_RUNTIME_CLASS_H
#define SHIP_JVM_RUNTIME_CLASS_H

#include <stdint.h>
#include <stdlib.h>

#include "classfile.h"

struct jclass
{
  uint16_t constant_pool_count;
  struct cp_info *constant_pool; // size = constant_pool_count
  uint16_t access_flags;
  UTF8_info this_class;
  UTF8_info super_class;
  uint16_t interfaces_count;
  uint16_t *interfaces; // size = interfaces_count
  uint16_t fields_count;
  struct field_info *fields; // size = fields_count
  uint16_t methods_count;
  struct method_info *methods; // size = methods_count
  uint16_t attributes_count;
  struct attribute_info **attributes; // size = attributes_count
};

#endif