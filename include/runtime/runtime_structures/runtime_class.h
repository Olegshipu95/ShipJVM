#ifndef SHIP_JVM_RUNTIME_CLASS_H
#define SHIP_JVM_RUNTIME_CLASS_H

#include <stdint.h>
#include <stdlib.h>

#include "classfile.h"
#include "runtime_constpool.h"

#include "util.h"

struct jclass
{
  uint16_t runtime_cp_count; // constant_pool_count - 1
  struct runtime_cp *runtime_cp; // size = runtime_cp_count
  /**
   * Access flags (ACC_PUBLIC, ACC_FINAL, etc.)
   */
  uint16_t access_flags;
  string this_class;
  string super_class;
  uint16_t interfaces_count;
  uint16_t *interfaces; // size = interfaces_count
  uint16_t fields_count;
  struct field_info *fields; // size = fields_count
  uint16_t methods_count;
  struct method_info *methods; // size = methods_count
  uint16_t attributes_count;
  struct attribute_info **attributes; // size = attributes_count
};

int jclass_new (struct jclass **jclass, struct class_file *class_file);

#endif