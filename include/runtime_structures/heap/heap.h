#ifndef SHIP_JVM_HEAP_H
#define SHIP_JVM_HEAP_H

#include "java_types.h"
#include "runtime_class.h"
#include <stdint.h>

#define INITIAL_HEAP_CAPACITY 5000
#define MAX_OBJECTS 65536

struct classloader;

typedef struct heap_object
{
  struct jclass *jclass;
  jvariable *variables; // Один jvariable на каждое поле
  uint8_t marked;       // Для будущего GC
} heap_object;

struct heap
{
  size_t capacity;
  size_t used;
  void *memory;                 // Блок непрерывной памяти
  struct heap_object **objects; // Таблица всех активных объектов
  size_t object_count;
};

int heap_init (struct heap **heap);
void heap_destroy (struct heap *java_heap);

heap_object *heap_alloc_object (struct classloader *loader, struct heap *heap,
                                struct jclass *jclass);

#endif
