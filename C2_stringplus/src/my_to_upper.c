#include "my_string.h"

void *my_to_upper(const char *str) {
  my_size_t n;
  char *buf = my_NULL;

  buf = (char *)(str);
  if (buf != my_NULL) {
    for (n = 0; n < my_strlen(buf); n++) {
      if (buf[n] > 96 && buf[n] < 123) {
        buf[n] -= 32;
      }
    }
  }
  return buf;
}