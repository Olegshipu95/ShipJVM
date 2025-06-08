#ifndef SHIP_JVM_JVM_STRUCTURE_H
#define SHIP_JVM_JVM_STRUCTURE_H


struct classloader;
struct heap;
struct jclass;
struct call_stack;

struct jvm
{
  struct jclass *main_class;
  struct classloader *classloader;
  struct call_stack *call_stack;
  struct heap *heap;
};

struct jvm* new_jvm ();

#endif
