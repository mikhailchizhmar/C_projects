#include "my_string.h"

char *my_strstr(const char *haystack, const char *needle) {
  char *res = my_NULL;
  if (*needle != 0) {
    for (char *buf = (char *)needle; *haystack != 0 && res == my_NULL;) {
      for (; *buf != 0 && *haystack != 0 && *haystack == *buf;
           buf++, haystack++) {
      }
      if (*buf == 0) {
        res = (char *)(haystack - (buf - needle));
      }
      if (*haystack != 0) haystack++;
    }
  } else {
    res = (char *)haystack;
  }
  return res;
}