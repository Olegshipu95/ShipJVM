#ifndef SHIP_JVM_RUNTIME_CP_H
#define SHIP_JVM_RUNTIME_CP_H

#include "constant_pool.h"
#include "java_types.h"

struct runtime_cp
{
  enum CONSTANT_POOL_TAG tag;

  union
  {
    string utf8;                                            // 1
    jint integer_info;                                      // 3
    jfloat float_info;                                      // 4
    jlong long_info;                                        // 5
    jdouble double_info;                                    // 6
    string class_name;                                      // 7
    string string_info;                                     // 8
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

int runtime_constant_new (struct runtime_cp **runtime_cp,
                          struct cp_info *cp_info,
                          uint16_t constant_pool_count);

#endif