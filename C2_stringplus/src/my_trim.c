#include "my_string.h"

char *my_reverse(char *str) {
  char buf[my_strlen(str)];
  int n = my_strlen(str) - 1, m = 0;

  while (n != -1) {
    buf[m++] = str[n--];
  }
  buf[m] = '\0';
  str[0] = '\0';
  my_strcat(str, buf);
  return str;
}

void *my_trim(const char *src, const char *trim_chars) {
  char *temp_src = (char *)(src);
  char *temp_trim_chars = (char *)(trim_chars);
  char empty_trim_char[12] = " \n\t\v\f\r";
  my_size_t n, m, l;
  int a, r = 0;

  if (temp_src != my_NULL) {
    char buf[my_strlen(temp_src)];
    if (temp_trim_chars == my_NULL || temp_trim_chars[0] == '\0') {
      temp_trim_chars = empty_trim_char;
    }
    while (r != 2) {
      for (n = 0, a = 0;
           temp_src[n] != '\0' && a != (int)my_strlen(temp_trim_chars); n++) {
        for (m = 0, a = 0; temp_trim_chars[m] != '\0'; m++) {
          if (temp_src[n] != temp_trim_chars[m]) {
            a++;
          }
        }
      }
      n -= 1;
      l = 0;
      while (temp_src[n] != '\0') {
        buf[l++] = temp_src[n++];
      }
      buf[l] = '\0';
      temp_src[0] = '\0';
      my_strcat(temp_src, buf);
      my_reverse(temp_src);
      r++;
    }
  }
  return temp_src;
}