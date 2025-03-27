#ifndef SHIP_JVM_CLASSFILE_H
#define SHIP_JVM_CLASSFILE_H
#include <stdint.h>

struct attribute_info {
  uint16_t attribute_name_index;
  uint32_t attribute_length;
  uint8_t* info; // size = attribute_length
};

struct field_info {
  uint16_t             access_flags;
  uint16_t             name_index;
  uint16_t             descriptor_index;
  uint16_t             attributes_count;
  struct attribute_info* attributes; // size = attributes_count
};

struct method_info {
  uint16_t             access_flags;
  uint16_t             name_index;
  uint16_t             descriptor_index;
  uint16_t             attributes_count;
  attribute_info* attributes; // size = attributes_count
};

struct ClassFile {
  uint32_t magic;
  uint16_t minor_version;
  uint16_t major_version;
  uint16_t constant_pool_count;
  struct cp_info* constantPool; // size = constant_pool_count
  uint16_t access_flags;
  uint16_t this_class;
  uint16_t super_class;
  uint16_t interfaces_count;
  uint16_t* interfaces; // size = interfaces_count
  uint16_t fields_count;
  struct field_info* fields; // size = fields_count
  uint16_t methods_count;
  struct method_info* methods; // size = methods_count
  uint16_t attributes_count;
  struct attribute_info* attributes; // size = attributes_count
};

#endif