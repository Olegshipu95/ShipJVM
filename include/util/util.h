#ifndef SHIP_JVM_UTIL_H
#define SHIP_JVM_UTIL_H

#include <stdint.h>
#include <stdlib.h>

#define my_alloc(T) ((T *)malloc (sizeof (T)))
#define my_alloc_array(T, n) ((T *)malloc (sizeof (T) * (size_t)(n)))

#define prerr(fmt, ...) printf ("ERROR: " fmt "\n", ##__VA_ARGS__)

#define PANIC(fmt, ...)                                                       \
  do                                                                          \
    {                                                                         \
      (void)fprintf (stderr, "\n\n\n*** (panic) *** [%s:%d]: " fmt "\n\n\n",  \
                     __FILE__, __LINE__, ##__VA_ARGS__);                      \
      exit (1);                                                               \
    }                                                                         \
  while (0)

size_t strlen (const char *str);

typedef char *string;

void *memcpy (void *dst, const void *src, size_t len);
void *memset (void *dst, int c, size_t len);
int memcmp (const void *buffer1, const void *buffer2, size_t count);

int is_string_match (uint8_t *str, size_t len, const char *expected);

#endif
