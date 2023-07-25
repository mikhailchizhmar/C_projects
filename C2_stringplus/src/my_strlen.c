#include "my_string.h"

my_size_t my_strlen(const char *str) {
  my_size_t res = 0;
  for (; *str != '\0'; str++, res++) {
  }
  return res;
}