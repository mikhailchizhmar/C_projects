#include "SmartCalc.h"

// char functions[9][4] = {"cos",  "sin",  "tan", "acos", "asin",
//                         "atan", "sqrt", "ln",  "log"};

int is_number(char c) { return (c >= '0' && c <= '9' ? TRUE : FALSE); }

int is_sign(char c) {
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' ? TRUE
                                                                   : FALSE);
}

int is_start_of_function(char c) {
  return (c == 'c' || c == 's' || c == 't' || c == 'a' || c == 'l' ? TRUE
                                                                   : FALSE);
}

int is_mod_before(char str[], int i) {
  return (i > 3 && str[i - 1] == 'd' && str[i - 2] == 'o' && str[i - 3] == 'm'
              ? TRUE
              : FALSE);
}

int is_cos(char str[], int i) {
  return (i < (int)strlen(str) - 5 && str[i + 1] == 'o' && str[i + 2] == 's' &&
                  str[i + 3] == '('
              ? TRUE
              : FALSE);
}

int is_sin(char str[], int i) {
  return (i < (int)strlen(str) - 5 && str[i + 1] == 'i' && str[i + 2] == 'n' &&
                  str[i + 3] == '('
              ? TRUE
              : FALSE);
}

int is_tan(char str[], int i) {
  return (i < (int)strlen(str) - 5 && str[i + 1] == 'a' && str[i + 2] == 'n' &&
                  str[i + 3] == '('
              ? TRUE
              : FALSE);
}

int is_function(char str[], int i) {
  int shift = 0;
  if (str[i] == 'c') {
    if (is_cos(str, i)) shift = 2;
  } else if (str[i] == 's') {
    if (is_sin(str, i)) {
      shift = 2;
    } else if (i < (int)strlen(str) - 6 && str[i + 1] == 'q' &&
               str[i + 2] == 'r' && str[i + 3] == 't' && str[i + 4] == '(')
      shift = 3;
  } else if (str[i] == 't') {
    if (is_tan(str, i)) shift = 2;
  } else if (str[i] == 'a') {
    if (is_cos(str, i + 1) || is_sin(str, i + 1) || is_tan(str, i + 1))
      shift = 3;
  } else if (str[i] == 'l') {
    if (i < (int)strlen(str) - 4 && str[i + 1] == 'n' && str[i + 2] == '(') {
      shift = 1;
    } else if (i < (int)strlen(str) - 5 && str[i + 1] == 'o' &&
               str[i + 2] == 'g' && str[i + 3] == '(')
      shift = 2;
  }
  /*помимо определения, является ли набор символов функцией, на выходе мы
   получаем число, на которое нужно сдвинуть i в валидации, чтобы не
   проверять другие символы*/
  return shift;
}

/* int only_digits(char str[]) {
  int result = 1;
  for (int i = 0; str[i] != '\0' && result == 1; i++) {
    if (!is_number(str[i]) && str[i] != 'x' && str[i] != ' ')
    result = 0;
  }
  return result;
} */
/* при данной реализации будет отсеиваться случай, когда введено одно число, а
это плохо */

int only_one_dot(char *str) {  // отсеить ввод по типу "125.5.7"
  int only_one_dot = TRUE;
  int count_dot = 0;
  for (int i = 0, j = 0; str[i] != '\0' && only_one_dot == TRUE; i++) {
    count_dot = 0;
    if (str[i] == '.' || is_number(str[i])) {
      j = i;
      while (str[j] == '.' || is_number(str[j])) {
        if (str[j] == '.') count_dot++;
        j++;
      }
      i = j;
    }
    if (count_dot > 1) only_one_dot = FALSE;
  }
  return only_one_dot;
}

int delete_space(char str[]) {
  int space_after_dot_or_char = FALSE;  // отсеить ввод по типу "123. 6"
  char copy[256] = "";
  int shift = 0;
  for (int i = 0, j = 0; str[i] != '\0'; i++) {
    shift = 0;
    if (str[i] == '.') {
      if ((str[i + 1] == ' ') || (i != 0 && str[i - 1] == ' '))
        space_after_dot_or_char = TRUE;
    }

    if (is_start_of_function(str[i])) {
      shift = is_function(str, i);
      if (!shift) {
        space_after_dot_or_char = TRUE;
      } else {
        for (int k = 0; k <= shift; k++) {
          copy[j + k] = str[i + k];
        }
      }
      i += shift;
      j += shift + 1;
    } else {
      if (str[i] != ' ') {
        copy[j] = str[i];
        j++;
      }
    }
  }
  copy[strlen(copy)] = '\0';
  strcpy(str, copy);
  return space_after_dot_or_char;
}

int check_brackets(char str[]) {
  int count = 0;
  for (int i = 0; str[i] && count >= 0; i++) {
    if (str[i] == '(') {
      if (i != (int)strlen(str) - 1 && str[i + 1] == ')') {
        count = -1;
      } else
        count++;
    }
    if (str[i] == ')') count--;
  }
  return count;
  // проверка на скобки
}

void check_dot(char str[], int i, int *output) {
  if (i == 0 || i == (int)strlen(str) - 1 || !is_number(str[i + 1]) ||
      (i != 0 && !is_number(str[i - 1]))) {
    *output = ERROR;
  }
  // если встретилась точка, после неё и перед ней должно быть число
}

void check_sign(char str[], int i, int *output) {
  int condition_after_sign =
      (i == (int)strlen(str) - 1 ||
       (str[i + 1] != '(' && str[i + 1] != 'x' && !is_number(str[i + 1]) &&
        !is_start_of_function(str[i + 1])));

  int condition_before_unary_sign =
      (i != 0 && str[i - 1] != '(' && str[i - 1] != ')' && str[i - 1] != 'x' &&
       !is_number(str[i - 1]));

  int condition_before_sign =
      (i == 0 ||
       (!is_number(str[i - 1]) && str[i - 1] != ')' && str[i - 1] != 'x'));

  if (condition_after_sign) *output = ERROR;
  if (str[i] == '+' || str[i] == '-') {
    if (condition_before_unary_sign) *output = ERROR;
  } else {
    if (condition_before_sign) *output = ERROR;
  }
  // если встретился знак, после него должно идти число, скобка или функция
}

void check_mod(char str[], int i, int *output) {
  int condition_before_mod =
      (i == 0 ||
       (str[i - 1] != 'x' && !is_number(str[i - 1]) && str[i - 1] != ')'));

  int condition_after_mod =
      (i > (int)(strlen(str) - 4) || str[i + 1] != 'o' || str[i + 2] != 'd' ||
       (str[i + 3] != 'x' && !is_number(str[i + 3]) && str[i + 3] != '('));

  if (condition_before_mod || condition_after_mod) *output = ERROR;
  // после mod нет скобок, а только число, x или "(" (возможно функция или "+-")
  // перед mod может быть только x, число или ")"
  // mod не может стоять в начале или конце
}

void check_x(char str[], int i, int *output) {
  int condition_before_x = (i > 0 && str[i - 1] != '(' &&
                            !is_sign(str[i - 1]) && !is_mod_before(str, i));

  int condition_after_x = (i < (int)strlen(str) - 1 && str[i + 1] != ')' &&
                           !is_sign(str[i + 1]) && str[i + 1] != 'm');

  if (condition_before_x || condition_after_x) *output = ERROR;
  // перед x может быть: ничего, "(", оператор или mod
  // после x можеть быть: ничего, ")", оператор или mod
}

void check_number(char str[], int i, int *output) {
  int condition_before_number =
      (i > 0 && str[i - 1] != '(' && str[i - 1] != '.' &&
       !is_sign(str[i - 1]) && !is_number(str[i - 1]) &&
       !is_mod_before(str, i));

  int condition_after_number =
      (i < (int)strlen(str) - 1 && str[i + 1] != '.' && str[i + 1] != ')' &&
       !is_sign(str[i + 1]) && !is_number(str[i + 1]) && str[i + 1] != 'm');

  if (condition_before_number || condition_after_number) *output = ERROR;
}

int validation(char str[]) {
  int output = OK;
  if (check_brackets(str) || delete_space(str) || !only_one_dot(str))
    output = ERROR;
  for (int i = 0; str[i] != '\0' && output; i++) {
    if (str[i] == '.') {
      check_dot(str, i, &output);
    } else if (is_sign(str[i])) {
      check_sign(str, i, &output);
    } else if (str[i] == 'm') {
      check_mod(str, i, &output);
      i += 2;
    } else if (str[i] == 'x') {
      check_x(str, i, &output);
    } else if (is_number(str[i])) {
      check_number(str, i, &output);
    } else if (str[i] == '(' || str[i] == ')') {
      continue;
    } else if (is_start_of_function(str[i])) {
      i += is_function(str, i);
    } else
      output = ERROR;
  }

  return output;
}