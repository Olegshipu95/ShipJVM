#ifndef SHIP_JVM_CONSTANT_POOL_H
#define SHIP_JVM_CONSTANT_POOL_H

#include <stdio.h>
#include <stdint.h>

enum CONSTANT_POOL_TAG {
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

struct UTF8_info{
  uint16_t lenght;
  char* string;
};

struct integer_info{
  uint32_t bytes;
};

struct float_info{
  uint32_t bytes;
};

struct long_info{
  uint32_t high_bytes;
  uint32_t low_bytes;
};

struct double_info{
  uint32_t high_bytes;
  uint32_t low_bytes;
};

struct class_info{
  uint16_t name_index;
};

struct string_info{
  uint16_t string_index;
};

struct ref_type_abstract{
  uint16_t class_index;
  uint16_t name_and_type_index;
};

struct fieldref_info{
  struct ref_type_abstract fieldref; 
};

struct methodref_info{
  struct ref_type_abstract methodref; 
};

struct interface_meth_ref_info{
  struct ref_type_abstract interf_meth_ref;
};

struct name_and_type_info{
  uint16_t name_index;
  uint16_t descripror_index;
};

struct method_handle_info{
  uint8_t reference_kind;
  uint16_t reference_index;
};

struct method_type_info {
  uint16_t descriptor_index;
};

struct dynamic_absract_info{
  uint16_t bootstrap_method_attr_index;
  uint16_t name_and_type_index;
};

struct dynamic_info {
  struct dynamic_absract_info dynamic;
};

struct invoke_dynamic_info {
  struct dynamic_absract_info invoke_dynamic;
};

struct module_info {
  uint16_t name_index;
};

struct package_info {
  uint16_t name_index;
};

struct cp_info {
  uint8_t tag;
  union constant_info
  {
    struct UTF8_info utf8_info; // 1
    struct integer_info integer_info; // 3
    struct float_info float_info; // 4
    struct long_info long_info; // 5
    struct double_info double_info; // 6
    struct class_info class_info; // 7
    struct string_info string_info; // 8
    struct fieldref_info fieldref_info; // 9
    struct methodref_info methodref_info; // 10
    struct interface_meth_ref_info interface_meth_ref_info; // 11
    struct name_and_type_info name_and_type_info; // 12
    struct method_handle_info method_handle_info; // 15
    struct method_type_info method_type_info; // 16
    struct dynamic_info dynamic_info; // 17
    struct invoke_dynamic_info invoke_dynamic_info; // 18
    struct module_info module_info; // 19
    struct package_info package_info; // 20
  } constant_info;
};


#endif