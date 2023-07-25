#include "my_string.h"

int my_sscanf(const char *str, const char *format, ...) {
  int res = 0, out_c = 0, res_n = 0;
  if (str != my_NULL && *str != '\0') {
    char *temp_str = (char *)str, part_str[my_strlen(str)],
         *temp_part_str = part_str;
    va_list args;
    my_flags flags = {0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0};
    va_start(args, format);
    for (char *c = (char *)format; *c && out_c != -1; c++) {
      if ((*c > ' ' && *c != '%')) {
        if (*c == *temp_str)
          temp_str++, res_n++;
        else
          out_c = -1;
      } else if (*c == '%' && *(c + 1) == '%') {
        c += 1;
        if (*c == *temp_str)
          temp_str++, res_n++;
        else
          out_c = -1;
      } else if (*c == '%' && *(c + 1) != '%') {
        my_sparse_flags(&flags, &c);
        my_scan_choice_spec(&flags, &args, &temp_str, temp_part_str, c, &res,
                             &res_n, &out_c);
      } else if (*c == ' ' || *c == '\n' || *c == '\t' || *c == '\v') {
        my_del_cont_chr_parse_input_str(&temp_str, &res_n);
      }
      my_flags_rebut(&flags);
    }
  } else {
    res = -1;
  }
  return res;
}

int my_sparse_flags(my_flags *flags, char **c) {
  char *all_args = "cdieEfgGosuxXpn%";
  int res = 0;
  while (res == 0 && my_strchr(all_args, *++(*c)) == my_NULL) {
    if (my_isdig(*(*c)) != 0) {
      flags->width = my_str_dig(c);
    } else if (*(*c) == '*') {
      flags->aster = 1;
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

int my_parse_input_str(char **str, char *str_part, char *c, int len,
                        int *res_n) {
  char temp_c = *c;
  int out = 1, temp_len = len;
  if (temp_c != 'c' && temp_c != 's') {
    my_del_cont_chr_parse_input_str(str, res_n);
    if (*(*str) != '\0') {
      my_check_type_of_num_spec_i(*str, &temp_c);
      if (temp_len <= 0) temp_len = -1;
      if (my_check_nan_inf_feg(str, str_part, &temp_len) < 3) {
        my_cp_part_shif_inp(str, str_part, &temp_c, &temp_len);
        my_check_parse_e(str, str_part, &temp_c, &temp_len);
      }
    } else {
      out = -1;
    }
  } else if (temp_c == 'c') {
    *str_part = *(*str);
    (*str)++;
    str_part++;
    *str_part = '\0';
  } else if (temp_c == 's') {
    my_del_cont_chr_parse_input_str(str, res_n);
    if (temp_len <= 0) {
      temp_len = -1;
    }
    my_cp_part_shif_inp(str, str_part, &temp_c, &temp_len);
  }
  if (out != -1 && my_strlen(str_part) == 0) out = 0;
  return out;
}

void my_check_parse_e(char **str, char *str_part, char *temp_c,
                       int *temp_len) {
  if ((*(*str) == 'e' || *(*str) == 'E') && *temp_len != 0) {
    char *temp_part = my_strchr(str_part, '\0');
    *temp_part = *(*str), *str += 1, temp_part += 1, *temp_len -= 1;
    my_cp_part_shif_inp(str, temp_part, temp_c, temp_len);
    if (*temp_part == '\0')
      *(temp_part - 1) = '\0';  // if temp_part empty we need delete last
                                // char in str_part
  }
}

int my_check_nan_inf_feg(char **str, char *str_part, int *len) {
  int out = 0, out_cic = 0;
  char *temp_str = *str;
  if (*temp_str == '-' || *temp_str == '+') temp_str += 1, out += 1;
  if (*temp_str == 'N' && *(temp_str + 1) == 'A' && *(temp_str + 2) == 'N')
    out += 3;
  if (*temp_str == 'n' && *(temp_str + 1) == 'a' && *(temp_str + 2) == 'n')
    out += 3;
  if (*temp_str == 'I' && *(temp_str + 1) == 'N' && *(temp_str + 2) == 'F')
    out += 3;
  if (*temp_str == 'i' && *(temp_str + 1) == 'n' && *(temp_str + 2) == 'f')
    out += 3;
  if (out >= 3) {
    out_cic = out;
    while (out_cic != 0 && *len != 0) {
      *str_part = *(*str);
      (*str)++;
      str_part++;
      out_cic--, *len -= 1;
    }
    *str_part = '\0';
  }
  return out;
}
void my_check_type_of_num_spec_i(char *str, char *c) {
  char *temp = str;
  if (*temp == '-' || *temp == '+') temp++;
  if (*c == 'i' && *temp == '0') {
    *c = 'o';
    ++temp;
    if (*temp == 'x' || *temp == 'X') {
      *c = 'x';
    }
  } else if (*c == 'i') {
    *c = 'd';
  }
}

void my_cp_part_shif_inp(char **str, char *str_part, char *c, int *len) {
  int out = *len;
  if ((*(*str) == '-' || *(*str) == '+') && *c != 's') {
    *str_part = *(*str), *str += 1, str_part += 1, out -= 1;
  }
  while ((*(*str) != ' ' && *(*str) != '\n' && *(*str) != '\t' &&
          *(*str) != '\v') &&
         out != 0 && *(*str) != '\0') {
    if (check_chr_for_parse_dig(*(*str), c) == 1) {
      *str_part = *(*str);
      (*str)++;
      str_part++;
      out -= 1;
      *len = out;
    } else {
      out = 0;
    }
  }
  *str_part = '\0';
}

void my_del_cont_chr_parse_input_str(char **str, int *res_n) {
  while ((*(*str) == ' ' || *(*str) == '\n' || *(*str) == '\t' ||
          *(*str) == '\v') &&
         *(*str) != '\0') {
    (*str)++;
    *res_n += 1;
  }
}

int check_chr_for_parse_dig(char str, char *c) {
  int out = 0;
  if (*c == 'd') {
    if ((str >= '0' && str <= '9')) out = 1;
  } else if (*c == 'f' || *c == 'e' || *c == 'E' || *c == 'g' || *c == 'G') {
    if ((str >= '0' && str <= '9') || str == '.') out = 1;
  } else if (*c == 'u') {
    if ((str >= '0' && str <= '9')) out = 1;
  } else if (*c == 'o') {
    if ((str >= '0' && str <= '7')) out = 1;
  } else if (*c == 'p') {
    if ((str >= '0' && str <= '9') || (str >= 'a' && str <= 'f') ||
        (str >= 'A' && str <= 'F') || str == 'x' || str == 'X')
      out = 1;
  } else if (*c == 'x' || *c == 'X') {
    if ((str >= '0' && str <= '9') || (str >= 'a' && str <= 'f') ||
        (str >= 'A' && str <= 'F') || str == 'x' || str == 'X')
      out = 1;
  } else {
    out = 1;
  }
  return out;
}
void my_scan_choice_spec(my_flags *flags, va_list *args, char **temp_str,
                          char *temp_part_str, char *c, int *res, int *res_n,
                          int *out_c) {
  int temp_out = 1;
  if (*c != 'n') {
    temp_out =
        my_parse_input_str(temp_str, temp_part_str, c, flags->width, res_n);
  }
  if (temp_out == 1 || *c == 'c') {
    if (*c == 'c') {
      if (flags->width == 0) flags->width = 1;
      my_sspec_c(flags, args, temp_part_str, res, res_n);
    } else if (*c == 's') {
      flags->width *= (flags->l == 1) ? 2 : 1;

      my_sspec_s(flags, args, temp_part_str, res, res_n);
    } else if ((*c == 'd') || (*c == 'i')) {
      my_sspec_d_i(flags, args, c, temp_part_str, res, res_n);
    } else if (*c == 'u' || *c == 'x' || *c == 'X' || *c == 'o') {
      my_sspec_ouxX(flags, args, c, temp_part_str, res, res_n);
    } else if (*c == 'p') {
      my_sspec_p(args, temp_part_str, res, res_n);
    } else if (*c == 'n') {
      my_spec_n(flags, args, res_n);
    } else if (*c == 'f' || *c == 'e' || *c == 'E' || *c == 'g' || *c == 'G') {
      my_sspec_efg(flags, args, temp_part_str, res, res_n);
    } else {
    }
  } else {
    if (temp_out == -1) *res = -1;
    *out_c = -1;
  }
}

void my_sspec_c(my_flags *flags, va_list *args, char *str, int *res,
                 int *res_n) {
  if (flags->aster != 1) {
    if (flags->l == 1) {
      wchar_t *c2 = va_arg(*args, wchar_t *);
      if ((int)mbtowc(c2, str, 1) == -1) *res = -1;
    } else {
      char *c2 = va_arg(*args, char *);
      if (*str != '\0') *c2 = *str;
    }
    if (*str != '\0' && *res != -1) {
      *res += 1;
      *res_n += 1;
    }
  }
}

void my_sspec_s(my_flags *flags, va_list *args, char *str, int *res,
                 int *res_n) {
  if (flags->l == 1) {
    wchar_t *c2 = va_arg(*args, wchar_t *);
    if ((int)mbstowcs(c2, str, my_strlen(str)) == -1) *res = -1;
  } else {
    char *c2 = va_arg(*args, char *);
    if (*str != '\0') my_strcpy(c2, str);
  }
  if (*str != '\0' && *res != -1) {
    *res += 1;
    *res_n += my_strlen(str);
  }
}

void my_sspec_p(va_list *args, char *str, int *res, int *res_n) {
  int base = 16, min = 0;
  if (*str != '\0') {
    *res_n += my_strlen(str);
    if (*str == '-') {
      min = 1;
      str++;
    } else if (*str == '+') {
      str++;
    }
    if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) str += 2;
    unsigned long long dig = my_str_to_ull(str, base);
    if (min == 1) dig = (unsigned long long)(-((unsigned long long)dig));
    int **temp_ptr = va_arg(*args, void *);
    *temp_ptr = (int *)dig;
    *res += 1;
  }
}

void my_sspec_d_i(my_flags *flags, va_list *args, char *c, char *str,
                   int *res, int *res_n) {
  int sign = 0;
  unsigned long long val = 0;
  *res_n += my_strlen(str);
  if (*str == '-') {
    sign = 1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  if (*str != 0 && flags->aster != 1) {
    if (*c == 'i' && *str == '0') {
      str++;
      if (*str == 'x' || *str == 'X') {
        str++;
        val = my_str_to_ll(str, 16, sign);
      } else {
        val = my_str_to_ll(str, 8, sign);
      }
    } else {
      val = my_str_to_ll(str, 10, sign);
    }
    if (flags->h == 1) {
      short int *val2 = va_arg(*args, short int *);
      (sign == 1) ? (*val2 = -val) : (*val2 = val);
    } else if (flags->l == 1) {
      long int *val2 = va_arg(*args, long int *);
      (sign == 1) ? (*val2 = -val) : (*val2 = val);
    } else {
      int *val2 = va_arg(*args, int *);
      (sign == 1) ? (*val2 = -val) : (*val2 = val);
    }
    *res += 1;
  }
}

void my_sspec_ouxX(my_flags *flags, va_list *args, char *c, char *str,
                    int *res, int *res_n) {
  unsigned long long val = 0;
  int sign = 0;
  *res_n += my_strlen(str);
  if (*str == '-')
    sign = 1, str++;
  else if (*str == '+')
    str++;
  else if (*c == 'o' && *str == '0')
    str++;
  if (*str != 0 && flags->aster != 1) {
    if (*c == 'o') {
      val = my_str_to_ull(str, 8);
    } else if (*c == 'u') {
      val = my_str_to_ull(str, 10);
    } else if (*c == 'x' || *c == 'X') {
      if ((my_strncmp(str, "0x", 2) == 0) ||
          (my_strncmp(str, "0X", 2) == 0)) {
        str += 2;
      }
      val = my_str_to_ull(str, 16);
    }
    if (flags->h == 1) {
      unsigned short int *val2 = va_arg(*args, unsigned short int *);
      (sign == 1) ? (*val2 = -val) : (*val2 = val);
    } else if (flags->l == 1) {
      unsigned long long int *val2 = va_arg(*args, unsigned long long int *);
      (sign == 1) ? (*val2 = -val) : (*val2 = val);
    } else {
      unsigned int *val2 = va_arg(*args, unsigned int *);
      (sign == 1) ? (*val2 = -val) : (*val2 = val);
    }
    *res += 1;
  }
}

void my_sspec_efg(my_flags *flags, va_list *args, char *str, int *res,
                   int *res_n) {
  long double val = 0;
  int sign = 0;
  *res_n += my_strlen(str);
  if (*str == '-') {
    sign = 1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  if (*str != 0 && flags->aster != 1) {
    if (my_strcmp(str, "NAN") == 0 || my_strcmp(str, "nan") == 0) {
      val = NAN;
    } else if (my_strcmp(str, "INF") == 0 || my_strcmp(str, "inf") == 0) {
      val = INFINITY;
    } else {
      val = my_str_to_ld(str);
    }
    if (flags->L == 1) {
      long double *val2 = va_arg(*args, long double *);
      (sign == 1) ? (*val2 = -val) : (*val2 = val);
    } else {
      float *val2 = va_arg(*args, float *);
      (sign == 1) ? (*val2 = -val) : (*val2 = val);
    }

    *res += 1;
  }
}

long long my_str_to_ll(char *str, unsigned int base, int sign) {
  long long temp_int = 0, shift = 0;
  unsigned int overflow = 0, digit = 0;
  int temp;
  for (; overflow == 0 && *str != '\0'; str++) {
    if (my_def_chr_str_to_ull(*str, &temp) == 0) {
      digit = *str - temp;
      if (digit >= base) overflow = 1;
      shift = base * temp_int;
      if (shift / base != temp_int) overflow = 1;
      temp_int = shift + digit;
      if (temp_int < digit) overflow = 1;
      if (overflow == 1) {
        temp_int = (sign == 0) ? LONG_MAX : LONG_MIN;
        sign = 0;
      }
    } else {
      temp_int = 0;
      overflow = 1;
    }
  }
  return temp_int;
}

unsigned long long my_str_to_ull(char *str, unsigned int base) {
  unsigned long long temp_int = 0, shift = 0;
  unsigned int overflow = 0, digit = 0;
  int temp;
  for (; overflow == 0 && *str != '\0'; str++) {
    if (my_def_chr_str_to_ull(*str, &temp) == 0) {
      digit = *str - temp;
      if (digit >= base) overflow = 1;
      shift = base * temp_int;
      if (shift / base != temp_int) overflow = 1;
      temp_int = shift + digit;
      if (temp_int < digit) overflow = 1;
      if (overflow == 1) temp_int = 18446744073709551615ULL;
    } else {
      temp_int = 0;
      overflow = 1;
    }
  }
  return temp_int;
}

int my_def_chr_str_to_ull(char str, int *temp) {
  int out = 0;
  if (str > '`' && str < 'g')
    *temp = 'W';
  else if (str > '@' && str < 'G')
    *temp = '7';
  else if (str > '/' && str < ':')
    *temp = '0';
  else
    out = -1;
  return out;
}

long double my_str_to_ld(char *str) {
  long double result = 0.;
  int exp = 0, cou_before_dot = -1, mant_size = 0, frac_exp = 0, exp_sign = 0;
  char *ptr_exp = my_NULL, *ptr_str = str;
  mant_size = my_cal_mant_str_to_db(&ptr_str, &cou_before_dot);
  if (*ptr_str != '\0') ptr_exp = ptr_str;
  ptr_str = str;
  frac_exp = my_cal_frac_exp_str_to_db(&mant_size, cou_before_dot);
  if (mant_size != 0) {
    result = my_res_cal_str_to_db(&ptr_str, mant_size);
    if (ptr_exp != my_NULL) {
      ptr_str = ptr_exp;
      exp = my_cal_exp_str_to_db(ptr_str, &exp_sign, frac_exp);
      result = my_cal_res_exp_str_to_db(exp, exp_sign, result);
    } else {
      if (frac_exp < 0) {
        frac_exp = -frac_exp;
        exp_sign = 1;
      } else {
        exp_sign = 0;
      }
      result = my_cal_res_exp_str_to_db(frac_exp, exp_sign, result);
    }
  } else {
    result = 0.0;
  }
  return result;
}

int my_cal_mant_str_to_db(char **ptr_str, int *cou_before_dot) {
  int mant_size = 0, out = 0, dig = 0;
  for (mant_size = 0; out != 1; mant_size++) {
    dig = *(*ptr_str);
    if (my_isdig(dig) != 1) {
      if ((dig != '.') || (*cou_before_dot >= 0)) out = 1;
      if (out != 1) *cou_before_dot = mant_size;
    }
    if (out != 1) (*ptr_str)++;
  }
  mant_size--;
  if (*cou_before_dot < 0) {
    *cou_before_dot = mant_size;
  } else {
    mant_size--;
  }
  return mant_size;
}

int my_cal_frac_exp_str_to_db(int *mant_size, int cou_before_dot) {
  int frac_exp = 0;
  if (*mant_size > 21) {
    frac_exp = cou_before_dot - 21;
    *mant_size = 21;
  } else {
    frac_exp = cou_before_dot - *mant_size;
  }
  return frac_exp;
}

long double my_res_cal_str_to_db(char **ptr_str, int mant_size) {
  long long frac1 = 0, frac2 = 0;
  long double result = 0., temp_frac2 = 0.;
  frac1 = my_calc_part_str_to_db(3, &mant_size, ptr_str);
  frac2 = my_calc_part_str_to_db(0, &mant_size, ptr_str);
  result = frac1;
  if (frac1 > 0) result *= 1000;
  temp_frac2 = frac2;
  result += temp_frac2;
  return result;
}

long long my_calc_part_str_to_db(int count, int *mant_size, char **ptr_str) {
  long long frac = 0;
  int dig = 0;
  for (; *mant_size > count; (*mant_size)--) {
    dig = *(*ptr_str);
    (*ptr_str)++;
    if (dig == '.') {
      dig = *(*ptr_str);
      (*ptr_str)++;
    }
    frac = 10 * frac + (dig - '0');
  }
  return frac;
}

int my_cal_exp_str_to_db(char *ptr_str, int *exp_sign, int frac_exp) {
  int exp = 0;
  if (*ptr_str == 'e' || *ptr_str == 'E' || *ptr_str == 'g' ||
      *ptr_str == 'G') {
    ptr_str++;
    if (*ptr_str == '-') {
      *exp_sign = 1;
      ptr_str++;
    } else if (*ptr_str == '+') {
      *exp_sign = 0;
      ptr_str++;
    }
    exp = my_toint(ptr_str);
    if (*exp_sign == 1)
      exp = frac_exp - exp;
    else
      exp = frac_exp + exp;
    if (exp < 0) {
      *exp_sign = 1;
      exp = -exp;
    } else {
      *exp_sign = 0;
    }
    if (exp > 511) exp = 511;
  }
  return exp;
}

long double my_cal_res_exp_str_to_db(int exp, int exp_sign,
                                      long double result) {
  long double db_Exp = 1.0, out = result;
  while (exp > 0) {
    db_Exp *= 10;
    exp--;
  }
  if (exp_sign == 1)
    out /= db_Exp;
  else
    out *= db_Exp;
  return out;
}