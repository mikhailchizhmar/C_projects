#include "my_string.h"

char *my_strerror(int errnum) {
  char temp[12];
  char *res = my_NULL;
  static char out[50];
#if __linux__
  char *str[135] = LINUX;
  if (errnum >= 0 && errnum <= 133) {
    res = str[errnum];
  } else {
    my_strcpy(out, "Unknown error ");
    my_llint_to_char(errnum, temp, -1, 0);
    res = my_strcat(out, temp);
    res = out;
  }
#elif __APPLE__
  char *mac[108] = APPLE;
  if (errnum >= 0 && errnum <= 106) {
    res = mac[errnum];
  } else {
    my_strcpy(out, "Unknown error: ");
    my_llint_to_char(errnum, temp, -1, 0);
    res = my_strcat(out, temp);
  }
#endif
  return res;
}

void my_llint_to_char(long long int n, char *res, int accur, int plus) {
  char str[22 + accur];
  int i = 0, j = 0, minus = 0;
  if (n == LONG_MIN) {
    n /= 10;
    str[i++] = 8 + '0';
  }
  if (n < 0) {
    n *= -1;
    minus++;
  }
  if (n == 0 && accur != 0) {
    str[i++] = '0';
  }
  while (n) {
    str[i++] = n % 10 + '0';
    n /= 10;
  }
  if (accur != -1 && accur > i) {
    while (accur > i) {
      str[i++] = '0';
    }
  }
  if (minus) {
    str[i++] = '-';
  } else if (plus != 0) {
    str[i++] = '+';
  }
  while (i--) {
    res[j++] = str[i];
  }
  res[j] = '\0';
}