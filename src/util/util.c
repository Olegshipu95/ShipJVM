#include "util.h"

int
is_utf8_match (uint8_t *buff, size_t len, const char *expected)
{
  const char *str = (const char *)buff;
  if (len != strlen (expected))
    {
      return 0;
    }
  return memcmp (str, expected, len) == 0;
}