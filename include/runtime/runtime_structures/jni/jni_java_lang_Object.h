#ifndef SHIP_JVM_JNI_JAVA_LANG_OBJECT_H
#define SHIP_JVM_JNI_JAVA_LANG_OBJECT_H

#include "jni.h"

int native_Object_init (struct stack_frame *frame);
int native_Object_registerNatives (struct stack_frame *frame);
int native_Object_hashCode (struct stack_frame *frame);
int native_Object_clone (struct stack_frame *frame);
int native_Object_notify (struct stack_frame *frame);
int native_Object_notifyAll (struct stack_frame *frame);
int native_Object_wait (struct stack_frame *frame);
int native_Object_wait_with_timeout (struct stack_frame *frame);
int native_Object_wait_with_timeout_nanos (struct stack_frame *frame);

extern const struct jni_native_method java_lang_Object_natives[];

#endif
