#include "my_string.h"

int my_strncmp(const char *str1, const char *str2, my_size_t n) {
  int out = 0;
  for (my_size_t i = 0; i < n && out == 0; i++, str1++, str2++) {
    if (*str1 != *str2) {
      out = *str1 - *str2;
    }
  }
  return out;
}