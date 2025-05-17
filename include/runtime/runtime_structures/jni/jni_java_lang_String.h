#ifndef SHIP_JVM_JNI_JAVA_LANG_STRING_H
#define SHIP_JVM_JNI_JAVA_LANG_STRING_H

#include "jni.h"

int native_String_init (struct stack_frame *frame);

extern const struct jni_native_method *java_lang_String_natives;

#endif