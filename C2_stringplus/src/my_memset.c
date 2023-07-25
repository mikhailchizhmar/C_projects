#include "my_string.h"

void *my_memset(void *str, int c, my_size_t n) {
  unsigned char *buf = (unsigned char *)str;
  if (buf != my_NULL) {
    for (my_size_t i = 0; i < n; i++) {
      buf[i] = c;
    }
  }
  return buf;
}