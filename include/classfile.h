#ifndef SHIP_JVM_CLASSFILE_H
#define SHIP_JVM_CLASSFILE_H

#include <stdint.h>
#include <stdlib.h>

#include "attribute_info.h"
#include "constant_pool.h"

struct field_info
{
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  struct attribute_info **attributes; // size = attributes_count
};

struct method_info
{
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  struct attribute_info *attributes; // size = attributes_count
};

struct class_file
{
  uint32_t magic;
  uint16_t minor_version;
  uint16_t major_version;
  uint16_t constant_pool_count;
  struct cp_info *constant_pool; // size = constant_pool_count
  uint16_t access_flags;
  uint16_t this_class;
  uint16_t super_class;
  uint16_t interfaces_count;
  uint16_t *interfaces; // size = interfaces_count
  uint16_t fields_count;
  struct field_info *fields; // size = fields_count
  uint16_t methods_count;
  struct method_info *methods; // size = methods_count
  uint16_t attributes_count;
  struct attribute_info *attributes; // size = attributes_count
};

void init_class_file (struct class_file *class);
int get_constant (struct class_file *class, uint16_t index,
                  struct cp_info **cp_info);
#endif