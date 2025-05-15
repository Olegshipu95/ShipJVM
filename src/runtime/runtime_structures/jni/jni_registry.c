#include "jni_registry.h"

extern const struct jni_native_method java_lang_Object_natives[];

static const struct jni_native_class jni_classes[]
    = { { "java/lang/Object", java_lang_Object_natives }, { NULL, NULL } };

native_func_t
lookup_native (const char *class_name, const char *method_name,
               const char *descriptor)
{
  for (int i = 0; jni_classes[i].class_name; i++)
    {
      if (strcmp (jni_classes[i].class_name, class_name) == 0)
        {
          const struct jni_native_method *methods = jni_classes[i].methods;
          for (int j = 0; methods[j].method_name; j++)
            {
              if (strcmp (methods[j].method_name, method_name) == 0
                  && strcmp (methods[j].descriptor, descriptor) == 0)
                {
                  return methods[j].func;
                }
            }
        }
    }
  return NULL;
}