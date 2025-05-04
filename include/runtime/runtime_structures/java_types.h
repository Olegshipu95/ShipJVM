#ifndef SHIP_JVM_JAVA_TYPES_H
#define SHIP_JVM_JAVA_TYPES_H

#include <errno.h>
#include <stdint.h>

typedef void *jobject; // Basic reference type

typedef uint8_t jboolean;
typedef int8_t jbyte;
typedef uint16_t jchar;
typedef int16_t jshort;

typedef int32_t jint;
typedef int32_t jfloat;

typedef int64_t jlong;
typedef int64_t jdouble;

typedef jint jsize;

// dimension of data types
typedef union jvalue
{
  jboolean z;
  jbyte b;
  jchar c;
  jshort s;
  jint i;
  jlong j;
  jfloat f;
  jdouble d;
  jobject l;
} jvalue;

typedef enum java_value_type
{
  JBOOLEAN = 0,
  JBYTE = 1,
  JCHAR = 2,
  JSHORT = 3,
  JINT = 4,
  JLONG = 5,
  JFLOAT = 6,
  JDOUBLE = 7,
  JOBJECT = 8
} java_value_type;

typedef struct jvariable
{
  java_value_type type;
  jvalue value;
} jvariable;

#endif