#ifndef SHIP_JVM_CONSTANT_POOL_H
#define SHIP_JVM_CONSTANT_POOL_H

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "classfile_stream.h"
#include "util.h"

enum CONSTANT_POOL_TAG
{
  UTF8 = 1,
  INTEGER = 3,
  FLOAT = 4,
  LONG = 5,
  DOUBLE = 6,
  CLASS = 7,
  STRING = 8,
  FIELD_REF = 9,
  METHOD_REF = 10,
  INTERF_METHOD_REF = 11,
  NAME_AND_TYPE = 12,
  METHOD_HANDLE = 15,
  METHOD_TYPE = 16,
  DYNAMIC = 17,
  INVOKE_METHOD = 18,
  MODULE = 19,
  PACKAGE = 20,
};

struct UTF8_info
{
  uint16_t lenght;
  uint8_t *bytes;
};

struct abstract_primitive
{
  uint32_t bytes;
};

struct integer_info
{
  struct abstract_primitive info;
};

struct float_info
{
  struct abstract_primitive info;
};

struct abstract_big_primitive
{
  uint32_t high_bytes;
  uint32_t low_bytes;
};

struct long_info
{
  struct abstract_big_primitive info;
};

struct double_info
{
  struct abstract_big_primitive info;
};

// Index of UTF8_info with class name
struct class_info
{
  uint16_t name_index;
};

// Index of UTF8_info with string content
struct string_info
{
  uint16_t string_index;
};

struct abstract_ref_type
{
  uint16_t class_index;         // Index of CONSTANT_Class_info
  uint16_t name_and_type_index; // Index of CONSTANT_NameAndType_info
};

struct fieldref_info
{
  struct abstract_ref_type info;
};

struct methodref_info
{
  struct abstract_ref_type info;
};

struct interface_meth_ref_info
{
  struct abstract_ref_type info;
};

struct name_and_type_info
{
  uint16_t name_index;       // Index of UTF8_info with name
  uint16_t descripror_index; // Index of UTF8_info with descriptor
};

struct method_handle_info
{
  uint8_t reference_kind;
  uint16_t reference_index; // index of abstract_ref_type
};

// Index of UTF8_info with method descriptor

struct method_type_info
{
  uint16_t descriptor_index;
};

struct absract_dynamic_info
{
  /*
  There must be exactly one BootstrapMethods attribute in the attributes table
  of a ClassFile structure if the constant_pool table of the ClassFile
  structure has at least one CONSTANT_InvokeDynamic_info entry
  */
  uint16_t bootstrap_method_attr_index;
  uint16_t name_and_type_index;
};

struct dynamic_info
{
  struct absract_dynamic_info info;
};

struct invoke_dynamic_info
{
  struct absract_dynamic_info info;
};

// Index of UTF8_info with module name

struct module_info
{
  uint16_t name_index;
};

// Index of UTF8_info with package name

struct package_info
{
  uint16_t name_index;
};

struct cp_info
{
  enum CONSTANT_POOL_TAG tag;

  union
  {
    struct UTF8_info utf8_info;                             // 1
    struct integer_info integer_info;                       // 3
    struct float_info float_info;                           // 4
    struct long_info long_info;                             // 5
    struct double_info double_info;                         // 6
    struct class_info class_info;                           // 7
    struct string_info string_info;                         // 8
    struct fieldref_info fieldref_info;                     // 9
    struct methodref_info methodref_info;                   // 10
    struct interface_meth_ref_info interface_meth_ref_info; // 11
    struct name_and_type_info name_and_type_info;           // 12
    struct method_handle_info method_handle_info;           // 15
    struct method_type_info method_type_info;               // 16
    struct dynamic_info dynamic_info;                       // 17
    struct invoke_dynamic_info invoke_dynamic_info;         // 18
    struct module_info module_info;                         // 19
    struct package_info package_info;                       // 20
  };
};

int read_utf8_info (Loader *loader, struct UTF8_info *utf8);
int read_primitive_info (Loader *loader, struct abstract_primitive *info);
int read_big_primitive_info (Loader *loader,
                             struct abstract_big_primitive *info);
int read_class_info (Loader *loader, struct class_info *info);
int read_string_info (Loader *loader, struct string_info *info);
int read_ref_type_info (Loader *loader, struct abstract_ref_type *info);
int read_name_and_type_info (Loader *loader, struct name_and_type_info *info);
int read_method_handle_info (Loader *loader, struct method_handle_info *info);
int read_method_type_info (Loader *loader, struct method_type_info *info);
int read_dynamic_info (Loader *loader, struct absract_dynamic_info *info);
int read_module_info (Loader *loader, struct module_info *info);
int read_package_info (Loader *loader, struct package_info *info);

#endif