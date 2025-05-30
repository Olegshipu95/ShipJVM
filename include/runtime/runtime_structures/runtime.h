#ifndef SHIP_JVM_RUNTIME_COMMON_H
#define SHIP_JVM_RUNTIME_COMMON_H
#include "classloader.h"
#include "jvm_structure.h"
#include "runtime_class.h"
#include "stack_frames.h"
#include "util.h"

int run_jvm (struct jvm *jvm);
#endif