#include "heap.h"

int
heap_init (struct heap **new_heap)
{
  struct heap *heap = my_alloc (struct heap);
  heap->capacity = INITIAL_HEAP_CAPACITY;
  heap->used = 0;
  heap->memory = malloc (INITIAL_HEAP_CAPACITY);
  if (!heap->memory)
    return -1;

  heap->objects = calloc (sizeof (struct heap_object *), MAX_OBJECTS);
  if (!heap->objects)
    {
      free (heap->memory);
      free (heap);
      return -1;
    }

  heap->object_count = 0;
  *new_heap = heap;
  return 0;
}

void
heap_destroy (struct heap *heap)
{
  for (size_t i = 0; i < heap->object_count; i++)
    {
      if (heap->objects[i])
        {
          free (heap->objects[i]->fields);
          free (heap->objects[i]);
        }
    }

  free (heap->objects);
  free (heap->memory);
  free (heap);
}

int
count_instance_fields (struct classloader *classloader, struct jclass *cls)
{
  if (!classloader || !cls)
    return 0;

  int count = 0;

  // Сначала считаем поля суперкласса
  if (cls->super_class)
    {
      struct jclass *super_cls = NULL;
      int err
          = classloader_load_class (classloader, cls->super_class, &super_cls);
      if (!err && super_cls) // Если загрузили успешно
        {
          count += count_instance_fields (classloader, super_cls);
        }
      else
        {
          prerr ("count_instance_fields: Failed to load superclass %s",
                 cls->super_class);
          // Можно не останавливать, просто не учитываем суперкласс
        }
    }

  // Теперь свои нестатические поля
  for (int i = 0; i < cls->fields_count; ++i)
    {
      struct rt_field *field = &cls->fields[i];
      if (!(field->access_flags & ACC_STATIC))
        count++;
    }

  return count;
}

heap_object *
heap_alloc_object (struct heap *heap, struct jclass *jclass)
{
  if (heap->object_count >= MAX_OBJECTS)
    {
      // В будущем здесь будет GC
      prerr ("Heap is full");
      return NULL;
    }

  size_t field_count = jclass->fields_count;
  heap_object *obj = my_alloc (heap_object);
  obj->jclass = jclass;
  obj->fields = my_alloc_array (jvariable, field_count);
  if (!obj->fields)
    {
      prerr ("Can not allocate object");
      free (obj);
      return NULL;
    }
  obj->marked = 0;

  heap->objects[heap->object_count++] = obj;
  return obj;
}