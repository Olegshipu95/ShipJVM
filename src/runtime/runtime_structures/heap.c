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
          free (heap->objects[i]->variables);
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

static int
fill_variable_types (struct classloader *classloader, struct jclass *cls,
                     jvariable *variables, uint16_t variable_count)
{
  if (!classloader || !cls || !variables)
    return -1;

  // Сначала обрабатываем суперкласс, если он есть
  if (cls->super_class)
    {
      struct jclass *super_cls = NULL;
      int err
          = classloader_load_class (classloader, cls->super_class, &super_cls);
      if (err)
        {
          prerr ("fill_variable_types: failed to load superclass %s",
                 cls->super_class);
          return -1;
        }

      err = fill_variable_types (classloader, super_cls, variables,
                                 variable_count);
      if (err)
        return err;
    }

  printf ("Object Fields of class %s: \n", cls->this_class);

  // Обработка текущих нестатических полей
  for (int i = 0; i < cls->fields_count; ++i)
    {
      struct rt_field *field = &cls->fields[i];

      if (field->access_flags & ACC_STATIC)
        continue;

      uint32_t slot = field->slot_id;
      if (slot >= variable_count)
        {
          prerr ("fill_variable_types: slot_id %u out of bounds (max %hu)",
                 slot, variable_count);
          return -1;
        }

      variables[slot] = field->data;

      // Debug вывод: тип поля и значение
      // Предполагаю, что у jvariable есть поле 'type' и в зависимости от типа
      // нужно выводить по-разному
      switch (variables[slot].type)
        {
        case JINT:
          printf ("Field name: %s, slot %u: int = %d\n", field->name, slot,
                  variables[slot].value._int);
          break;
        case JFLOAT:
          printf ("Field name: %s, slot %u: float = %f\n", field->name, slot,
                  variables[slot].value._float);
          break;
        case JLONG:
          printf ("Field name: %s, slot %u: long = %lld\n", field->name, slot,
                  (long long)variables[slot].value._long);
          break;
        case JDOUBLE:
          printf ("Field name: %s, slot %u: double = %f\n", field->name, slot,
                  variables[slot].value._double);
          break;
        case JOBJECT:
          printf ("Field name: %s, slot %u: object ptr = %p\n", field->name,
                  slot, variables[slot].value._object);
          break;
        default:
          printf ("Field name: %s, slot %u: unknown type %d\n", field->name,
                  slot, variables[slot].type);
        }
    }

  return 0;
}

heap_object *
heap_alloc_object (struct classloader *classloader, struct heap *heap,
                   struct jclass *jclass)
{
  if (!heap || !jclass)
    return NULL;

  if (heap->object_count >= MAX_OBJECTS)
    {
      prerr ("heap_alloc_object: Heap is full");
      return NULL;
    }

  uint16_t object_fields_count = jclass->object_fields_count;

  heap_object *obj = my_alloc (heap_object);
  if (!obj)
    return NULL;

  obj->jclass = jclass;
  obj->variables = calloc (object_fields_count, sizeof (jvariable));
  if (!obj->variables)
    {
      prerr ("heap_alloc_object: Failed to allocate fields");
      free (obj);
      return NULL;
    }

  obj->marked = 0;

  if (fill_variable_types (classloader, jclass, obj->variables,
                           object_fields_count)
      != 0)
    {
      prerr ("heap_alloc_object: Failed to fill variable types");
      free (obj->variables);
      free (obj);
      return NULL;
    }

  heap->objects[heap->object_count++] = obj;
  return obj;
}
