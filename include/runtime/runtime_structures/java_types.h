#ifndef SHIP_JVM_JAVA_TYPES_H
#define SHIP_JVM_JAVA_TYPES_H

#include <errno.h>
#include <stdint.h>
#include <stdio.h>

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
  jboolean _bool;
  jbyte _byte;
  jchar _char;
  jshort _short;
  jint _int;
  jlong _long;
  jfloat _float;
  jdouble _double;
  jobject _object;
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


jvariable create_variable (java_value_type type);


#endif