#include "my_string.h"

char *my_strcat(char *dest, const char *src) {
  char *buf1 = dest;
  while (*buf1 != '\0') {
    buf1++;
  }
  while (*src != '\0') {
    *buf1++ = *src++;
  }
  *buf1 = '\0';
  return dest;
}