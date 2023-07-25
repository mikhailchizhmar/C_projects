#include "my_string.h"

char *my_strrchr(const char *str, int c) {
  char ch = c;
  char *res = my_NULL;
  int len = my_strlen(str);
  for (; len >= 0; len--) {
    if (str[len] == ch) {
      res = (char *)&str[len];
      len = -1;
    }
  }

  return res;
}