#include "my_string.h"

char *my_strchr(const char *str, int c) {
  char *res = my_NULL;
  char ch = c;
  for (; *str != '\0' && *str != ch; str++) {
  }
  if (*str == ch) {
    res = (char *)str;
  }
  return res;
}