#ifndef SHIP_JVM_UTIL_H
#define SHIP_JVM_UTIL_H

#include <stdint.h>
#include <stdlib.h>

#define my_alloc(T) ((T *)malloc (sizeof (T)))
#define my_alloc_array(T, n) ((T *)malloc (sizeof (T) * (size_t)(n)))

#define prerr(fmt, ...) printf ("ERROR: " fmt "\n", ##__VA_ARGS__)

size_t strlen(const char *str);

void *memcpy(void *dst, const void *src, size_t len);

#endif
