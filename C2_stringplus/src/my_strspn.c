#include "my_string.h"

my_size_t my_strspn(const char *str1, const char *str2) {
  my_size_t res = 0, match, out_cic = 0;
  if (str1 != my_NULL && str2 != my_NULL) {
    for (; *str1 != '\0' && out_cic == 0; str1++) {
      match = 0;
      for (my_size_t i = 0; i < my_strlen(str2) && match == 0; i++) {
        if (*str1 == str2[i]) {
          match = 1;
          res++;
        }
      }
      if (match == 0) {
        out_cic = 1;
      }
    }
  }
  return res;
}