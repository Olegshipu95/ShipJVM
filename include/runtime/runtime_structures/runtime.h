#ifndef SHIP_JVM_RUNTIME_COMMON_H
#define SHIP_JVM_RUNTIME_COMMON_H
#include "classloader.h"
#include "runtime_class.h"

struct jvm
{
  struct jclass *main_class;
  struct classloader *classloader;
};

struct jvm *new_jvm ();
int run_jvm (struct jvm *jvm);
#endif