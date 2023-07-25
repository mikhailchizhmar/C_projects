#include "my_string.h"

char *my_strcpy(char *dest, const char *src) {
  char *buf = dest;
  for (; *src != '\0'; src++, buf++) {
    *buf = *src;
  }
  *buf = '\0';
  return dest;
}