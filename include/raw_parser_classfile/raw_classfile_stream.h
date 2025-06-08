#ifndef SHIP_JVM_RAW_CLASSFILE_STREAM_H
#define SHIP_JVM_RAW_CLASSFILE_STREAM_H
#include <stdint.h>
#include <stdio.h>

#include "util.h"

typedef struct
{
  FILE *file;
  int error;
} Loader;

uint8_t loader_u1 (Loader *loader);
uint16_t loader_u2 (Loader *loader);
uint32_t loader_u4 (Loader *loader);
uint64_t loader_u8 (Loader *loader);

#endif