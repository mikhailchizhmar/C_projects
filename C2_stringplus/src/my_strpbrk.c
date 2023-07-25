#include "my_string.h"

char *my_strpbrk(const char *str1, const char *str2) {
  char *res = my_NULL;
  for (; *str1 != '\0' && res == my_NULL; str1++) {
    for (my_size_t i = 0; str2[i] != '\0' && res == my_NULL; i++) {
      if (*str1 == str2[i]) {
        res = (char *)str1;
      }
    }
  }
  return res;
}