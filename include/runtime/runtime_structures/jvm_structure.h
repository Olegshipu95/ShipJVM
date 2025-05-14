#ifndef SHIP_JVM_JVM_STRUCTURE_H
#define SHIP_JVM_JVM_STRUCTURE_H

#include "heap.h"
#include "classloader.h"
#include "util.h"

struct jvm
{
  struct jclass *main_class;
  struct classloader *classloader;
  struct call_stack *call_stack;
  struct heap* heap;
};

struct jvm *new_jvm ();

#endif