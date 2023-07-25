#include "my_string.h"

int my_memcmp(const void *str1, const void *str2, my_size_t n) {
  unsigned char *buf1 = (unsigned char *)str1;
  unsigned char *buf2 = (unsigned char *)str2;
  int out = 0;
  for (my_size_t i = 0; i < n; i++, buf1++, buf2++) {
    if (*buf1 != *buf2) {
      out = *buf1 - *buf2;
      i = n;
    }
  }
  return out;
}