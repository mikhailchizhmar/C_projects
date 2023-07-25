#include "my_string.h"

void *my_memcpy(void *dest, const void *src, my_size_t n) {
  unsigned char *buf1 = (unsigned char *)dest;
  unsigned char *buf2 = (unsigned char *)src;
  if (buf1 != my_NULL && buf2 != my_NULL) {
    for (my_size_t i = 0; i < n; i++) {
      buf1[i] = buf2[i];
    }
  }
  return buf1;
}