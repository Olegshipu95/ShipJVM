#ifndef SHIP_JVM_CLASSFILE_H
#define SHIP_JVM_CLASSFILE_H

#include <stdint.h>
#include <stdlib.h>

#include "attribute_info.h"
#include "constant_pool.h"
#include "util.h"

struct field_info
{
  uint16_t access_flags;
  uint16_t name_index;       // CONSTANT_Utf8_info
  uint16_t descriptor_index; // CONSTANT_Utf8_info
  uint16_t attributes_count;
  struct attribute_info **attributes; // size = attributes_count
};

struct method_info
{
  uint16_t access_flags;
  uint16_t name_index;
  uint16_t descriptor_index;
  uint16_t attributes_count;
  struct attribute_info **attributes; // size = attributes_count
};

struct class_file
{
  /**
   * Magic number identifying class files (0xCAFEBABE)
   */
  uint32_t magic;

  /**
   * Minor version number of class file format
   */
  uint16_t minor_version;

  /**
   * Major version number of class file format
   * 45.3 = Java 1.1, 46 = Java 1.2, ..., 60 = Java 16
   */
  uint16_t major_version;

  /**
   * Number of entries in constant pool plus one
   * (Index 0 is invalid, entries start at 1)
   */
  uint16_t constant_pool_count;

  /**
   * Constant pool array (size is constant_pool_count-1)
   */
  struct cp_info *constant_pool; // size = constant_pool_count

  /**
   * Access flags (ACC_PUBLIC, ACC_FINAL, etc.)
   */
  uint16_t access_flags;

  /**
   * Index into constant pool of this class (CONSTANT_Class_info)
   */
  uint16_t this_class;

  /**
   * Index into constant pool of super class (0 for java/lang/Object)
   */
  uint16_t super_class;

  uint16_t interfaces_count;

  uint16_t *interfaces; // size = interfaces_count

  uint16_t fields_count;

  struct field_info *fields; // size = fields_count

  uint16_t methods_count;

  struct method_info *methods; // size = methods_count

  uint16_t attributes_count;

  struct attribute_info **attributes; // size = attributes_count
};

void init_class_file (struct class_file *class);

int get_constant (struct class_file *class, uint16_t index,
                  struct cp_info **cp_info);

struct UTF8_info *validate_constant (struct class_file *class, uint16_t index);
#endif