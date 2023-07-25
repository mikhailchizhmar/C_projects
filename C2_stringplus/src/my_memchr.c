#include "my_string.h"

void *my_memchr(const void *str, int c, my_size_t n) {
  unsigned char *buf = (unsigned char *)str;
  unsigned char *res = my_NULL;
  for (my_size_t i = 0; i < n; i++) {
    if (buf[i] == c) {
      res = &buf[i];
      i = n;
    }
  }
  return res;
}