#ifndef SHIP_JVM_RUNTIME_CLASS_H
#define SHIP_JVM_RUNTIME_CLASS_H

#include <stdint.h>
#include <stdlib.h>

#include "classfile.h"
#include "rt_attr_parser.h"
#include "runtime_constpool.h"

#include "util.h"

// access_flags
#define ACC_PUBLIC 0x0001
#define ACC_PRIVATE 0x0002
#define ACC_PROTECTED 0x0004
#define ACC_STATIC 0x0008
#define ACC_FINAL 0x0010
#define ACC_SYNCHRONIZED 0x0020
#define ACC_BRIDGE 0x0040
#define ACC_VARARGS 0x0080
#define ACC_NATIVE 0x0100
#define ACC_ABSTRACT 0x0400
#define ACC_STRICT 0x0800
#define ACC_SYNTHETIC 0x1000

struct rt_field
{
  uint16_t access_flags;
  string name;       // CONSTANT_Utf8_info
  string descriptor; // CONSTANT_Utf8_info
  uint16_t attributes_count;
  struct rt_attribute **attributes; // size = attributes_count
  jvariable data;
  uint32_t slot_id; // index of field in class.
};

struct rt_method
{
  uint16_t access_flags;
  string name;       // CONSTANT_Utf8_info
  string descriptor; // CONSTANT_Utf8_info
  uint16_t attributes_count;
  struct rt_attribute **attributes;    // size = attributes_count
  struct rt_code_attribute *code_attr; // NULL if method is abstract or native
};

struct rt_methods_data
{
  uint16_t methods_count;
  struct rt_method *methods; // size = methods_count
  // array of pointers to methods
  uint16_t static_methods_count;
  struct rt_method **static_methods;
  // array of pointers to methods
  uint16_t native_methods_count;
  struct rt_method **native_methods;
};

struct jclass
{
  uint16_t runtime_cp_count;     // constant_pool_count - 1
  struct runtime_cp *runtime_cp; // size = runtime_cp_count
  /**
   * Access flags (ACC_PUBLIC, ACC_FINAL, etc.)
   */
  uint16_t access_flags;
  string this_class;
  string super_class;
  uint16_t interfaces_count;
  string *interfaces; // size = interfaces_count
  uint16_t fields_count;
  struct rt_field *fields; // size = fields_count
  struct rt_methods_data methods_data;
  uint16_t attributes_count;
  struct rt_attribute **attributes; // size = attributes_count
  int initialized;                  // true if <clinit> is already executed
  int being_initialized;            // for recurse method
  uint16_t static_fields_size;
};

int jclass_new (struct jclass **jclass, struct class_file *class_file);
int find_method_in_current_class (struct jclass *class,
                                  struct rt_method **find_method,
                                  const char *name, const char *descriptor);
int find_field_in_current_class (struct jclass *cls,
                                 struct rt_field **out_field, const char *name,
                                 const char *descriptor);

int find_field_in_class_hierarchy (struct classloader *classloader,
                                   struct jclass *cls,
                                   struct rt_field **out_field,
                                   const char *name, const char *descriptor);

#endif