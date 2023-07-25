#include "my_string.h"

char *my_strncat(char *dest, const char *src, my_size_t n) {
  char *buf1 = dest;
  while (*buf1 != '\0') {
    buf1++;
  }
  for (my_size_t i = 0; i < n; i++) {
    *buf1++ = *src++;
  }
  *buf1 = '\0';
  return dest;
}