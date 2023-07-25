#include "my_string.h"

char *my_strtok(char *str, const char *delim) {
  static char *buf = 0;
  char *res = my_NULL;
  int out = 0;
  if (str)
    buf = str;
  else if (!buf)
    out = 1;
  if (out != 1) {
    str = buf + my_strspn(buf, delim);
    buf = str + my_strcspn(str, delim);
    if (buf != str) {
      buf = *buf ? *buf = 0, buf + 1 : 0;
      res = str;
    } else {
      res = my_NULL;
      buf = 0;
    }
  }
  return res;
}