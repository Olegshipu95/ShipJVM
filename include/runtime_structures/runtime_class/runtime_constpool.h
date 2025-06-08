#ifndef SHIP_JVM_RUNTIME_CP_H
#define SHIP_JVM_RUNTIME_CP_H

#include "java_types.h"
#include "raw_constant_pool.h"

struct rt_name_and_type
{
  string name;
  string descriptor;
};

struct rt_ref_type
{
  string class_name; // Index of CONSTANT_Class_info
  struct rt_name_and_type nat;
};
struct rt_fieldref
{
  struct rt_ref_type ref;
};

struct rt_methodref
{
  struct rt_ref_type ref;
};

struct rt_interface_meth_ref
{
  struct rt_ref_type ref;
};

typedef enum reference_types
{
  REF_getField = 1,
  REF_getStatic = 2,
  REF_putField = 3,
  REF_putStatic = 4,
  REF_invokeVirtual = 5,
  REF_invokeStatic = 6,
  REF_invokeSpecial = 7,
  REF_newInvokeSpecial = 8,
  REF_invokeInterface = 9,
  REF_INVALID = 999,
} reference_types;

struct rt_method_handle
{
  reference_types kind;
  struct rt_ref_type *reference_index;
};

typedef struct string_object
{
  string class_raw_data;
  jobject string_object;
} string_object;

struct runtime_cp
{
  enum CONSTANT_POOL_TAG tag;

  union
  {
    string utf8;                                    // 1
    jint integer_info;                              // 3
    jfloat float_info;                              // 4
    jlong long_info;                                // 5
    jdouble double_info;                            // 6
    string class_name;                              // 7
    string_object string_info;                      // 8
    struct rt_fieldref fieldref;                    // 9
    struct rt_methodref methodref;                  // 10
    struct rt_interface_meth_ref interf_meth;       // 11
    struct rt_name_and_type name_and_type;          // 12
    struct rt_method_handle method_handle;          // 15
    string method_type;                             // 16
    struct dynamic_info dynamic_info;               // 17
    struct invoke_dynamic_info invoke_dynamic_info; // 18
    string module;                                  // 19
    string package;                                 // 20
  };
};

int runtime_constant_new (struct runtime_cp **runtime_cp,
                          struct cp_info *cp_info,
                          uint16_t constant_pool_count);

void print_runtime_cp (struct runtime_cp *cp, uint16_t constant_pool_count);

int new_array_runtime_constpool (struct runtime_cp **runtime_cp,
                                 struct cp_info *cp_info,
                                 uint16_t constant_pool_count);

int index_to_string (string *dest, struct cp_info *cp_info,
                     uint16_t constant_pool_count, uint16_t index);

int parse_rt_index_to_string (struct runtime_cp *rt_cp, string *new_string,
                              uint16_t index, uint16_t runtime_cp_count);

int parse_rt_classname (struct runtime_cp *rt_cp, string *new_class_name,
                        uint16_t index, uint16_t runtime_cp_count);

#endif