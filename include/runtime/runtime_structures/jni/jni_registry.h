#ifndef SHIP_JVM_JNI_REGISTRY_H
#define SHIP_JVM_JNI_REGISTRY_H

#include "jni.h"
#include "native_types.h"

native_func_t lookup_native (const char *class_name, const char *method_name,
                             const char *descriptor);

#endif
