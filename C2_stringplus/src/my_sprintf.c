#include "my_string.h"

int my_sprintf(char *str, const char *format, ...) {
  int res = 0;
  if (str != my_NULL) {
    char *temp_str = str;
    va_list args;
    my_flags flags = {0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0};
    va_start(args, format);
    for (char *c = (char *)format; *c && res != -1; c++) {
      if (*c != '%') {
        temp_str[res++] = *c;
      } else {
        my_parse_flags(&flags, args, &c);
        my_choice_spec(&flags, &args, temp_str, c, &res);
      }
      my_flags_rebut(&flags);
    }
    temp_str[res] = '\0';
  } else {
    res = -1;
  }
  return res;
}

void my_choice_spec(my_flags *flags, va_list *args, char *temp_str, char *c,
                    int *res) {
  if (*c == 'c') {
    my_pspec_c(flags, args, c, temp_str, res);
  } else if (*c == 's') {
#if __linux__
    flags->zero = 0;
#endif
    my_pspec_s(flags, args, c, temp_str, res);
  } else if ((*c == 'd') || (*c == 'i')) {
    my_pspec_d_i(flags, args, c, temp_str, res);
  } else if (*c == 'u' || *c == 'x' || *c == 'X' || *c == 'o') {
    flags->space = 0;
    my_pspec_u_x_X_o(flags, args, c, temp_str, res);
  } else if (*c == 'p') {
    flags->hash = 2;
#if __APPLE__
    flags->plus = 0;
    flags->space = 0;
#endif
    my_pspec_p(flags, args, c, temp_str, res);
  } else if (*c == 'n') {
    my_spec_n(flags, args, res);
  } else if (*c == 'f') {
    my_efg_default_val(flags);
    my_pspec_f(flags, my_getld_efg(flags, args), c, temp_str, res);
  } else if (*c == 'e' || *c == 'E') {
    my_efg_default_val(flags);
    my_pspec_e(flags, my_getld_efg(flags, args), c, temp_str, res);
  } else if (*c == 'g' || *c == 'G') {
    my_efg_default_val(flags);
    my_pspec_g_G(flags, my_getld_efg(flags, args), c, temp_str, res);
  } else {
    char temp_char[2] = {*c, '\0'};
    my_add_to_str(temp_str, flags, temp_char, c, res);
  }
}
void my_efg_default_val(my_flags *flags) {
  if (flags->accur == -1) flags->accur = 6;
  flags->f_counter = 1;
}
void my_flags_rebut(my_flags *flags) {
  flags->min = 0;
  flags->plus = 0;
  flags->space = 0;
  flags->hash = 0;
  flags->zero = 0;
  flags->width = 0;
  flags->aster = 0;
  flags->dot = 0;
  flags->accur = -1;
  flags->h = 0;
  flags->l = 0;
  flags->L = 0;
  flags->f_counter = 0;
}

int my_parse_flags(my_flags *flags, va_list args, char **c) {
  char *all_args = "cdieEfgGosuxXpn%";
  int res = 0;
  while (res == 0 && my_strchr(all_args, *++(*c)) == my_NULL) {
    if (*(*c) == '-') {
      flags->min = 1, flags->zero = 0;
    } else if (*(*c) == '+') {
      flags->plus = 1;
    } else if (*(*c) == ' ') {
      flags->space = 1;
    } else if (*(*c) == '#') {
      flags->hash = 2;
    } else if (*(*c) == '0' && flags->min != 1) {
      flags->zero = 1;
    } else if (my_isdig(*(*c)) != 0) {
      flags->width = my_str_dig(c);
    } else if (*(*c) == '*') {
      flags->aster = 1;
      flags->width = va_arg(args, int);
    } else if (*(*c) == '.') {
      flags->dot = 1;
      if (*++(*c) == '*') {
        flags->accur = va_arg(args, int);
      } else if (my_isdig(*(*c)) != 0) {
        flags->accur = my_str_dig(c);
      } else {
        flags->accur = 0;
        (*c)--;
      }
    } else if (*(*c) == 'h' && flags->L != 1) {
      flags->h = 1;
    } else if (*(*c) == 'l' && flags->L != 1) {
      flags->l = 1;
    } else if (*(*c) == 'L' && flags->h != 1) {
      flags->L = 1;
    } else {
      res = -1;
    }
  }
  return res;
}

void my_add_to_str(char *temp_str, my_flags *flags, char *source, char *c,
                   int *res) {
  int width = my_strlen(source), spec_c_end_line = 0;
  if ((*c == 'c') && width == 0 && flags->width == 0) {
    width = 1;
    spec_c_end_line = 1;
  }
  int flag_width = flags->width;
  char fil_sim = ' ';
  if (flags->plus != 1 && flags->space == 1 && source[0] != '-' && *c != 'c' &&
      *c != 's') {
    temp_str[(*res)++] = ' ';
    flag_width--;
  }
  if (flags->zero != 0) {
    if (*c != 'c' && *c != 's' && source[0] == '-') {
      temp_str[(*res)++] = '-';
      width--, flag_width--, source++;
    } else if (*c != 'c' && *c != 's' && source[0] == '+') {
      temp_str[(*res)++] = '+';
      width--, flag_width--, source++;
    }
    fil_sim = '0';
  }
  if (flags->min != 0) {
    while (*source != '\0') {
      temp_str[(*res)++] = *source++;
    }
    for (int i = 0; i < flag_width - width; i++) {
      temp_str[(*res)++] = fil_sim;
    }
  } else {
    for (int i = 0; i < flag_width - width; i++) {
      temp_str[(*res)++] = fil_sim;
    }
    while (*source != '\0') {
      temp_str[(*res)++] = *source++;
    }
  }
  if (spec_c_end_line == 1) temp_str[(*res)++] = '\0';
}

void my_pspec_c(my_flags *flags, va_list *args, char *c, char *temp_str,
                int *res) {
#if __linux__
  flags->zero = 0;
#endif
  if (flags->l == 1) {
    wchar_t c2 = va_arg(*args, wchar_t);
    char long_chr[4] = {0, 0, 0, 0};
    if ((int)wctomb(long_chr, c2) != -1)
      my_add_to_str(temp_str, flags, long_chr, c, res);
    else
      *res = -1;
  } else {
    char c2 = va_arg(*args, int), temp_char[2] = {' ', '\0'};
    temp_char[0] = c2;
    my_add_to_str(temp_str, flags, temp_char, c, res);
  }
}

void my_pspec_s(my_flags *flags, va_list *args, char *c, char *temp_str,
                int *res) {
  if (flags->l == 1) {
    wchar_t *temp_wstr = va_arg(*args, wchar_t *);
    char long_chr[wcslen(temp_wstr) * 4];
    long_chr[0] = '\0';
    if ((int)wcstombs(long_chr, temp_wstr, sizeof(long_chr)) != -1) {
      my_accur_s(flags, long_chr);
      my_add_to_str(temp_str, flags, long_chr, c, res);
    } else {
      *res = -1;
    }
  } else {
    char *sour_str = va_arg(*args, char *);
    if (sour_str == my_NULL) {
      char temp_sour_str[7] = "(null)";
      my_accur_s(flags, temp_sour_str);
      my_add_to_str(temp_str, flags, temp_sour_str, c, res);
    } else {
      char temp_sour_str[my_strlen(sour_str)];
      temp_sour_str[0] = '\0';
      my_strcat(temp_sour_str, sour_str);
      my_accur_s(flags, temp_sour_str);
      my_add_to_str(temp_str, flags, temp_sour_str, c, res);
    }
  }
}

void my_pspec_d_i(my_flags *flags, va_list *args, char *c, char *temp_str,
                  int *res) {
  char first_part[22 + flags->accur];
  long long int temp_int;
  if (flags->l == 1) {
    temp_int = va_arg(*args, long long int);
    if (temp_int > -2147483648 && temp_int < 0)
      temp_int = (unsigned long int)temp_int;
  } else if (flags->h == 1) {
    temp_int = (short int)va_arg(*args, int);
  } else {
    temp_int = va_arg(*args, int);
  }
  my_llint_to_char(temp_int, first_part, flags->accur, flags->plus);
  my_add_to_str(temp_str, flags, first_part, c, res);
}

void my_pspec_u_x_X_o(my_flags *flags, va_list *args, char *c, char *temp_str,
                      int *res) {
  char first_part[22 + flags->accur + flags->hash];
  unsigned long long int temp_int;
  if (flags->l == 1) {
    temp_int = (unsigned long long int)va_arg(*args, long long int);
    if (temp_int < 2147483648) temp_int = (unsigned long int)temp_int;
  } else if (flags->h == 1) {
    temp_int = (unsigned short int)va_arg(*args, int);
  } else {
    temp_int = (unsigned int)va_arg(*args, int);
  }
  if (flags->hash > 0 && *c == 'o')
    flags->accur -= 1;
  else if (*c == 'u')
    flags->hash = 0;
  my_ullint_to_format_str(temp_int, c, first_part, flags);
  my_add_to_str(temp_str, flags, first_part, c, res);
}

void my_pspec_p(my_flags *flags, va_list *args, char *c, char *temp_str,
                int *res) {
  char first_part[22 + flags->accur + flags->hash];
  unsigned long long int temp_int;
  temp_int = (unsigned long long int)va_arg(*args, void *);
#if __linux__
  if (temp_int != 0) {
#endif
    my_ullint_to_format_str(temp_int, c, first_part, flags);
#if __linux__
  } else {
    my_strcpy(first_part, "(nil)");
    flags->space = 0;
  }
#endif

  my_add_to_str(temp_str, flags, first_part, c, res);
}

void my_spec_n(my_flags *flags, va_list *args, int *res) {
  if (flags->l == 1) {
    long int *temp_int = va_arg(*args, long *);
    *temp_int = *res;
  } else if (flags->h == 1) {
    short *temp_int = va_arg(*args, short *);
    *temp_int = *res;
  } else {
    int *temp_int = va_arg(*args, int *);
    *temp_int = *res;
  }
}

long double my_getld_efg(my_flags *flags, va_list *args) {
  long double temp_dou;
  if (flags->L == 1) {
    temp_dou = va_arg(*args, long double);
  } else {
    temp_dou = va_arg(*args, double);
  }
  return temp_dou;
}

void my_pspec_f(my_flags *flags, long double temp_dou, char *c, char *temp_str,
                int *res) {
  char first_part[400 + flags->accur], second_part[400 + flags->accur + 1],
      all[sizeof(first_part) + sizeof(second_part)];
  all[0] = '\0';
  if (check_nan_inf(all, temp_dou) == 0) {
    my_check_minus_ld(flags, &temp_dou, all);
    long double left, right = modfl(temp_dou, &left);
    unsigned long long int temp_int;
    my_f_right_ld(flags, second_part, c, &right, &left);
    if (left < 18446744073709551615ULL) {
      temp_int = left;
      my_pspec_fe_to_char(temp_int, c, first_part, flags, 0);
    } else {
      my_f_left_ld(first_part, &left);
    }
    my_strcat(all, first_part);
    if ((*c == 'g' || *c == 'G') && flags->hash == 0) my_del_zero(second_part);
    if ((flags->accur != 0 || flags->hash != 0) && my_strlen(second_part) != 0)
      my_strcat(all, ".\0");
    if (flags->accur != 0) my_strcat(all, second_part);
    my_add_to_str(temp_str, flags, all, c, res);
  } else {
    flags->zero = 0;
    my_add_to_str(temp_str, flags, all, c, res);
  }
}

void my_f_right_ld(my_flags *flags, char *second_part, char *c,
                   long double *right, long double *left) {
  int i = 0;
  unsigned long long temp_int;
  long double temp_left;
  while (i < flags->accur) {
    *right *= 10, i++;
  }
  *right = roundl(*right);
  temp_left = modfl(*right, right);
  if (*right < 18446744073709551615ULL) {
    temp_int = *right;
    if (temp_int == pow(10, flags->accur)) {
      *left += 1;
      temp_int -= temp_int;
    }
    my_pspec_fe_to_char(temp_int, c, second_part, flags, i);
  } else {
    flags->f_counter--;
    while (i >= 0) {
      *right /= 10, i--;
    }
    *right = modfl(*right, &temp_left);
    if (temp_left > 0) {
      *left += 1;
    }
    while (i < flags->accur) {
      *right *= 10;
      *right = modfl(*right, &temp_left);
      temp_int = temp_left;
      second_part[i++] = temp_int + '0';
    }
    second_part[i] = '\0';
  }
}

void my_f_left_ld(char *first_part, long double *left) {
  int i = 0, j = 0;
  unsigned long long temp_int;
  long double temp_left;
  while (*left >= 10) {
    *left /= 10;
    j++;
  }
  j++;
  i = 0;
  while (j-- != 0) {
    *left = modfl(*left, &temp_left);
    temp_int = temp_left;
    first_part[i++] = temp_int + '0';
    *left *= 10;
  }
  first_part[i] = '\0';
}

int my_pspec_e(my_flags *flags, long double temp_dou, char *c, char *temp_str,
               int *res) {
  char first_part[400 + flags->accur], second_part[400 + flags->accur + 1],
      all[sizeof(first_part) + sizeof(second_part)], sign = 0, exp, *ptr_dot;
  int cou_pow = 0;
  all[0] = '\0';
  if (check_nan_inf(all, temp_dou) == 0) {
    my_check_minus_ld(flags, &temp_dou, all);
    exp = (*c == 'e' || *c == 'g') ? 'e' : 'E';
    long double left, right = modfl(temp_dou, &left);
    unsigned long long int temp_int;
    sign = (temp_dou == 0.)
               ? '+'
               : my_esign_count_pow(&left, &right, &temp_dou, &cou_pow);
    my_f_right_ld(flags, second_part, c, &right, &left);
    temp_int = left;
    if (temp_int == 10) {
      cou_pow++;
      temp_int /= 10;
    }
    my_pspec_fe_to_char(temp_int, c, first_part, flags, 0);
    my_strcat(all, first_part);
    if (flags->accur != 0 || flags->hash != 0) my_strcat(all, ".\0");
    if ((*c == 'g' || *c == 'G') && flags->hash == 0) {
      my_del_zero(second_part);
      if (second_part[0] == '\0' && (ptr_dot = my_strchr(all, '.')) != my_NULL)
        *ptr_dot = '\0';
    }
    if (flags->accur != 0) my_strcat(all, second_part);
    my_wrt_e_end(all, cou_pow, sign, exp);
    my_add_to_str(temp_str, flags, all, c, res);
  } else {
    flags->zero = 0;
    my_add_to_str(temp_str, flags, all, c, res);
  }
  return (sign == '-') ? cou_pow * (-1) : cou_pow;
}

void my_del_zero(char *second_part) {
  int len_temp = my_strlen(second_part);
  char temp[len_temp];
  int i = 0;
  for (int j = len_temp - 1, stop = 0; j >= 0; j--) {
    if (second_part[j] == '0' && stop == 0) {
    } else {
      stop = 1;
      temp[i++] = second_part[j];
    }
  }
  temp[i] = '\0';
  my_reverse(temp);
  my_strcpy(second_part, temp);
}
void my_pspec_g_G(my_flags *flags, long double temp_dou, char *c,
                  char *temp_str, int *res) {
  char all[150 + flags->accur];
  all[0] = '\0';
  if (check_nan_inf(all, temp_dou) == 0) {
    int cou_pow = 0, temp = 0;
    cou_pow = my_pspec_e(flags, temp_dou, c, all, &temp);
    all[0] = '\0';
    flags->f_counter = 1;
    if (flags->accur == 0) {
      flags->accur = 1;
    }
    if ((flags->accur > cou_pow) & (cou_pow >= -4)) {
      flags->accur = flags->accur - 1 - cou_pow;
      my_pspec_f(flags, temp_dou, c, temp_str, res);
    } else {
      flags->accur -= 1;
      my_pspec_e(flags, temp_dou, c, temp_str, res);
    }
  } else {
    flags->zero = 0;
    my_add_to_str(temp_str, flags, all, c, res);
  }
}

int check_nan_inf(char *temp_str, long double temp_dou) {
  int out = 0;
  if (isnan(temp_dou)) {
    char temp_char[4] = {'n', 'a', 'n', '\0'};
    my_strcat(temp_str, temp_char);
    out = 1;
  } else if (isinf(temp_dou)) {
    char temp_char[4] = {'i', 'n', 'f', '\0'};
    my_strcat(temp_str, temp_char);
    out = 1;
  }
  return out;
}

char my_esign_count_pow(long double *left, long double *right,
                        long double *temp_dou, int *cou_pow) {
  char sign;
  unsigned long long temp_int;
  if (*left > 0) {
    sign = '+';
    while (*temp_dou >= 10) {
      *temp_dou /= 10;
      (*cou_pow)++;
    }
    *right = modfl(*temp_dou, left);
  } else {
    sign = '-';
    temp_int = *right;
    while (temp_int <= 0) {
      *right *= 10;
      temp_int = *right;
      (*cou_pow)++;
    }
    *right = modfl(*right, left);
  }
  return sign;
}

void my_wrt_e_end(char *all, int j, char sign, char exp) {
  char end[10] = {exp, sign, '\0'};
  char temp[8];
  int i = 0, k = 2;
  if (j < 10) {
    my_strcat(end, "0");
    temp[i++] = j % 10 + '0';
    temp[i++] = '\0';
    my_strcat(end, temp);
  } else {
    while (j && i < (int)sizeof(temp)) {
      temp[i++] = j % 10 + '0';
      j /= 10;
    }
    my_reverse_str(end, temp, &i, &k);
    end[k] = '\0';
  }
  my_strcat(all, end);
}

void my_check_minus_ld(my_flags *flags, long double *temp_dou, char *all) {
  if (*temp_dou < 0) {
    *temp_dou *= -1;
    all[0] = '-';
    all[1] = '\0';
  } else if (flags->plus != 0) {
    all[0] = '+';
    all[1] = '\0';
  } else {
    all[0] = '\0';
  }
}

void my_accur_s(my_flags *flags, char *long_chr) {
#if __linux__
  if (my_strcmp(long_chr, "(null)") == 0) {
    if (flags->accur == 0) {
      long_chr[flags->accur] = '\0';
    } else if (flags->accur < 7 && flags->accur > 0) {
      long_chr[0] = '\0';
    }
  } else {
#endif
    if (flags->accur != -1 && flags->accur < (int)my_strlen(long_chr)) {
      long_chr[flags->accur] = '\0';
    }
#if __linux__
  }
#endif
}

void my_pspec_fe_to_char(unsigned long long int n, char *c, char *res,
                         my_flags *flags, int cou_zero) {
  char str[22 + flags->accur + flags->hash];
  int i = 0, j = 0;
  my_add_ulldig_to_str(n, c, str, &i);
  if (cou_zero > i) {
    while (cou_zero != i) {
      str[i++] = '0';
    }
  }
  my_reverse_str(res, str, &i, &j);
  my_add_zero_to_str(res, flags->accur, &j, flags->f_counter);
  if (flags->f_counter > 0) {
    flags->f_counter--;
  }
  res[j] = '\0';
}

void my_ullint_to_format_str(unsigned long long int n, char *c, char *res,
                             my_flags *flags) {
  char str[22 + flags->accur + flags->hash];
  int i = 0, j = 0;
  unsigned long long int temp_n = n;
  if (n == 0 && flags->accur == 0) {
#if __linux__
    res[0] = '\0';
#elif __APPLE__
    if (*c == 'p') {
      str[i++] = 'x';
      str[i++] = '0';
      my_reverse_str(res, str, &i, &j);
      res[j] = '\0';
    } else {
      res[0] = '\0';
    }
#endif
  } else {
    my_add_ulldig_to_str(n, c, str, &i);
    my_add_zero_to_str(str, flags->accur, &i, 1);
    check_spec_add_0xX(flags, temp_n, c, str, &i);
    my_reverse_str(res, str, &i, &j);
    res[j] = '\0';
  }
}

void check_spec_add_0xX(my_flags *flags, unsigned long long int temp_n, char *c,
                        char *str, int *i) {
  if ((flags->hash != 0 && temp_n != 0) || *c == 'p') {
    if (*c == 'x' || *c == 'p') {
      str[(*i)++] = 'x';
      str[(*i)++] = '0';
      if (*c == 'p' && flags->plus != 0) str[(*i)++] = '+';
    } else if (*c == 'X') {
      str[(*i)++] = 'X';
      str[(*i)++] = '0';
    } else if (*c == 'o') {
      str[(*i)++] = '0';
    }
  }
}
void my_add_zero_to_str(char *res, int accur, int *j, int f_counter) {
  if (accur > *j && f_counter == 1) {
    while (accur > *j) {
      res[(*j)++] = '0';
    }
  }
}

void my_reverse_str(char *res, char *str, int *i, int *j) {
  while ((*i)--) {
    res[(*j)++] = str[*i];
  }
}

void my_add_ulldig_to_str(unsigned long long int n, char *c, char *str,
                          int *i) {
  int divid;
  if ((*c == 'x') || (*c == 'X') || (*c == 'p')) {
    divid = 16;
  } else if (*c == 'o') {
    divid = 8;
  } else {
    divid = 10;
  }
  if (n == 0) {
    str[(*i)++] = '0';
  }
  while (n) {
    str[(*i)++] = my_hex_to_chr(n % divid, c);
    n /= divid;
  }
}

char my_hex_to_chr(int hex, char *c) {
  char out;
  if (hex <= 9) {
    out = hex + '0';
  } else if (*c == 'x' || *c == 'p') {
    out = hex + 'W';
  } else if (*c == 'X') {
    out = hex + '7';
  }
  return out;
}
int my_str_dig(char **c) {
  char temp[11];
  my_get_str(temp, c);
  return my_toint(temp);
}

void my_get_str(char *temp, char **c) {
  int i = 0;
  while (my_isdig(*(*c)) != 0 && i < 11) {
    temp[i++] = *(*c);
    (*c)++;
  }
  temp[i] = '\0';
  (*c)--;
}

int my_isdig(char c) {
  int out = 0;
  if (c >= '0' && c <= '9') {
    out = 1;
  }
  return out;
}

int my_toint(char *temp) {
  int res = 0;
  while (my_isdig(*temp) == 1) {
    res = res * 10 + (*temp - '0');
    temp++;
  }
  return res;
}