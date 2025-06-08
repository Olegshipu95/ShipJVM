#ifndef SHIP_JVM_JNI_H
#define SHIP_JVM_JNI_H

#include "native_types.h"

struct jni_native_method
{
  const char *method_name;
  const char *descriptor;
  native_func_t func;
};

struct jni_native_class
{
  const char *class_name;
  const struct jni_native_method *methods;
};

#endif
