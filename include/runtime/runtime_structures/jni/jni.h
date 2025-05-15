#ifndef SHIP_JVM_JNI_H
#define SHIP_JVM_JNI_H

#include "stack_frames.h"
#include "util.h"

typedef int (*native_func_t) (struct stack_frame *frame);

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