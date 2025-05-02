#ifndef SHIP_JVM_RUNTIME_CP_H
#define SHIP_JVM_RUNTIME_CP_H

#include "constant_pool.h"

struct runtime_cp
{
  uint16_t cp_count;
  struct cp_info *cp;
};

int get_runtime_constant (struct runtime_cp *runtime_cp, uint16_t index,
                          struct cp_info **cp_info);

#endif