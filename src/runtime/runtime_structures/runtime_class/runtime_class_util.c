#include "runtime_class_util.h"

#include "classfile.h"
#include "rt_attr_parser.h"

int
find_method_in_current_class (struct jclass *class,
                              struct rt_method **find_method, const char *name,
                              const char *descriptor)
{
  if (!class || !name || !descriptor)
    {
      *find_method = NULL;
      return EINVAL;
    }

  // Ищем в методах текущего класса
  for (uint16_t i = 0; i < class->methods_data.methods_count; i++)
    {
      struct rt_method *method = &class->methods_data.methods[i];

      if (strcmp (method->name, name) == 0
          && strcmp (method->descriptor, descriptor) == 0)
        {
          *find_method = method;
          return 0;
        }
    }

  // Метод не найден
  printf ("Can not find method %s:%s in class %s\n", name, descriptor,
          class->this_class);
  *find_method = NULL;
  return -1;
}

int
find_field_in_current_class (struct jclass *cls, struct rt_field **out_field,
                             const char *name, const char *descriptor)
{
  if (!cls || !out_field || !name || !descriptor)
    return EINVAL;

  for (int i = 0; i < cls->fields_count; i++)
    {
      struct rt_field *field = &cls->fields[i];
      if (!field)
        continue;

      if (strcmp (field->name, name) == 0
          && strcmp (field->descriptor, descriptor) == 0)
        {
          *out_field = field;
          return 0; // Найдено
        }
    }

  return ENOENT; // Поле не найдено
}

int
find_field_in_class_hierarchy (struct classloader *classloader,
                               struct heap *heap, struct jclass *cls,
                               struct rt_field **out_field, const char *name,
                               const char *descriptor)
{
  if (!cls || !out_field || !name || !descriptor)
    return EINVAL;

  while (cls)
    {
      int err = find_field_in_current_class (cls, out_field, name, descriptor);
      if (err == 0)
        return 0; // Поле найдено

      if (!cls->super_class)
        break;

      struct jclass *super_cls = NULL;
      err = classloader_load_class (classloader, heap, cls->super_class,
                                    &super_cls);
      if (err != 0)
        return err;

      cls = super_cls;
    }

  return ENOENT; // Поле не найдено в иерархии
}
