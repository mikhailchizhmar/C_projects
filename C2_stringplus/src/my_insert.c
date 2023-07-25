#include "my_string.h"

char *my_cutstr(char *dest, char *src, int e) {
  int n = 0, m = 0;

  while (n != e) {
    n++;
  }
  while (src[n] != '\0') {
    dest[m++] = src[n++];
  }
  dest[m] = '\0';
  return (dest);
}

void *my_insert(const char *src, const char *str, my_size_t start_index) {
  my_size_t n = 0, m = 0, l = 0;
  char *temp_src = (char *)src;
  char *temp_str = (char *)str;

  if (temp_str != my_NULL && temp_src != my_NULL &&
      start_index <= my_strlen(src)) {
    char end_src[my_strlen(temp_src)];
    my_cutstr(end_src, temp_src, start_index);
    while (n < start_index) {
      n++;
    }
    while (temp_str[m] != '\0') {
      temp_src[n++] = temp_str[m++];
    }
    while (end_src[l] != '\0') {
      temp_src[n++] = end_src[l++];
    }
    temp_src[n] = '\0';
  } else {
    temp_src = my_NULL;
  }
  return temp_src;
}