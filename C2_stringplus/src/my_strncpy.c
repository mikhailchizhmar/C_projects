#include "my_string.h"

char *my_strncpy(char *dest, const char *src, my_size_t n) {
  char *buf = dest;
  my_size_t i = 0;
  for (; i < n; i++) {
    buf[i] = src[i];
  }

  return dest;
}