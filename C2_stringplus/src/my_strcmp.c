#include "my_string.h"

int my_strcmp(const char *str1, const char *str2) {
  while (*str1 != '\0' && *str1 == *str2) {
    str1++;
    str2++;
  }
  return *str1 - *str2;
}