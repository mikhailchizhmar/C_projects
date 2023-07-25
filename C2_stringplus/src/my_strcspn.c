#include "my_string.h"

my_size_t my_strcspn(const char *str1, const char *str2) {
  my_size_t res = 0, out_cic = 0;
  for (; *str1 != '\0' && out_cic == 0; str1++) {
    for (my_size_t i = 0; str2[i] != '\0' && out_cic == 0; i++) {
      if (*str1 == str2[i]) {
        out_cic = 1;
      }
    }
    if (out_cic != 1) {
      res++;
    }
  }
  return res;
}