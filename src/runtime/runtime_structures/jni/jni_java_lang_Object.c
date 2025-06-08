#include "jni_java_lang_Object.h"
#include "string.h"
#include "java_types.h"
#include "stack_frames.h"

int
native_Object_init (struct stack_frame *)
{
  return 0; // do nothing
}

int
native_Object_registerNatives (struct stack_frame *)
{
  return 0; // do nothing
}

int
native_Object_hashCode (struct stack_frame *frame)
{
  jvariable this_ref;
  if (opstack_pop (frame->operand_stack, &this_ref)
      || this_ref.type != JOBJECT)
    {
      prerr ("hashCode: invalid this");
      return EINVAL;
    }

  // Используем адрес объекта как хэш (или отдельное поле hash)
  jint hash = (jint)(uintptr_t)this_ref.value._object;

  jvariable result;
  result.type = JINT;
  result.value._int = hash;

  return opstack_push (frame->operand_stack, result);
}

int
native_Object_clone (struct stack_frame *)
{
  prerr ("clone: not implemented");
  return ENOTSUP;
}

int
native_Object_notify (struct stack_frame *)
{
  prerr ("notify: not implemented");
  return 0;
}

int
native_Object_notifyAll (struct stack_frame *)
{
  prerr ("notifyAll: not implemented");
  return 0;
}

int
native_Object_wait (struct stack_frame *)
{
  prerr ("wait: not implemented");
  return 0;
}

int
native_Object_wait_with_timeout (struct stack_frame *)
{
  prerr ("wait(long): not implemented");
  return 0;
}

int
native_Object_wait_with_timeout_nanos (struct stack_frame *)
{
  prerr ("wait(long, int): not implemented");
  return 0;
}

// Определения JNI-таблицы методов
const struct jni_native_method java_lang_Object_natives[]
    = { { "<init>", "()V", native_Object_init },
        { "registerNatives", "()V", native_Object_registerNatives },
        { "hashCode", "()I", native_Object_hashCode },
        { "clone", "()Ljava/lang/Object;", native_Object_clone },
        { "notify", "()V", native_Object_notify },
        { "notifyAll", "()V", native_Object_notifyAll },
        { "wait", "()V", native_Object_wait },
        { "wait", "(J)V", native_Object_wait_with_timeout },
        { "wait", "(JI)V", native_Object_wait_with_timeout_nanos },
        { NULL, NULL, NULL } };
