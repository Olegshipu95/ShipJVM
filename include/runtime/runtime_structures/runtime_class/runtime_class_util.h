#ifndef SHIP_JVM_RUNTIME_CLASS_UTIL_H
#define SHIP_JVM_RUNTIME_CLASS_UTIL_H

#include "classloader.h"
#include "heap.h"
#include "runtime_class.h"

int find_method_in_current_class (struct jclass *class,
                                  struct rt_method **find_method,
                                  const char *name, const char *descriptor);

int find_field_in_current_class (struct jclass *cls,
                                 struct rt_field **out_field, const char *name,
                                 const char *descriptor);

int find_field_in_class_hierarchy (struct classloader *classloader,
                                   struct heap *heap, struct jclass *cls,
                                   struct rt_field **out_field,
                                   const char *name, const char *descriptor);

#endif