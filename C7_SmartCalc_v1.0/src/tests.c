#include <check.h>

#include "SmartCalc.h"

void smart_calc_testing(SRunner **sr);

START_TEST(validation_test_1) {
  char str1[256] = "123.789";
  int expected_result = OK;
  int actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "6.09");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "9.");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, ".7");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "8. 2");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "56 .3");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "92 . 7");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "k.1");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "7.k");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "3.8.0");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "3..0");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(validation_test_2) {
  char str1[256] = "+7";
  int expected_result = OK;
  int actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "-9");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(3-6) + 2");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "x - 9");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "f - 0");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, ". + 34");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "6 ^ 4");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(32+ 7) / 5");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "x * 7");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "*6");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(^23)");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "$ / 3");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "3  + (2 * 7)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "2 * x");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "4 ^ cos(7)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "3-");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(6+)");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "3/ d");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "3+^ x");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(validation_test_3) {
  char str1[256] = "(-7)";
  int expected_result = OK;
  int actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, ")");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "()");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, ")(");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "((-7) + (+3))");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(34)*(-6)(");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(-95) + ((123)");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(validation_test_4) {
  char str1[256] = "mod 4";
  int expected_result = ERROR;
  int actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "4mod");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "5ma");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "5mod 3");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "6 mod x");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "x mod 9");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "x mod x");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "6mod(-8)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "7modh");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(-4)mod5");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "&mod8");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(validation_test_5) {
  char str1[256] = "5 mod x";
  int expected_result = OK;
  int actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "6 - x");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "x*23");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "7 / (x - 9)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(6 ^ x)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(4)x");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "x8");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "x.7");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "xh");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(validation_test_6) {
  char str1[256] = "5 mod 9";
  int expected_result = OK;
  int actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "21");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "6 - 34");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "8*23");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "7 / (32 - 9)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(6 ^ 45)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(4)33");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "9.5- 9764");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "8p");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(validation_test_7) {
  char str1[256] = "cos(9*x)";
  int expected_result = OK;
  int actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "3 + sin(5)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "1 / tan(54 - x)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "2 * acos(21)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "6 ^ asin(90)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "atan(12/x)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "2 / sqrt(123)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "ln(6 * x) - 7");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "log(5) ^ 4");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "lo g(5) ^ 4");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "atan (12/x)");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "lag(5) ^ 7");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "sin 5");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "cos(5");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "tan()");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "4 atan(9)");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(validation_test_8) {
  char str1[256] = "cos(9*h)";
  int expected_result = ERROR;
  int actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "3 + & sin(5)");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "szfhrewtn");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "5,9 + 7");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(validation_test_9) {
  char str1[256] = "(sin(2)+cos(3)) * sqrt(5)";
  int expected_result = OK;
  int actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "ln(10) - sin(2) / sqrt(3)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "tan(4) * cos(5) ^ sin(6)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "acos(0.5) + atan(0.8) * log(2)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "sqrt(9) + ln(4) - tan(1) / cos(2)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "sin(1) * cos(2) + sqrt(3) ^ tan(0.5)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "2 / sqrt(123)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "10 mod 3 + atan(0.6) - log(2)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "(sin(1) + cos(2) / sqrt(3)) * ln(4)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "sqrt(16) - tan(1) * acos(0.2)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "log (4) + sin(2) - cos(1) / sqrt(5)");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "log(4x) + sin(2,7) - cos(1) / sqrt(5)");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  strcpy(str1, "log(4) + sin(27) - cos(1) / sqr(5)");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);

  char str2[256] =
      "sin(1) * cos(2) + sqrt(3) ^ tan(0.5) * (sin(2)+cos(3)) * sqrt(5) / "
      "ln(10) - sin(2) / sqrt(3) ^ tan(4) * cos(5) ^ sin(6) - acos(0.5) + "
      "atan(0.8) * log(2) + 23456 * sqrt(9) + ln(4) - tan(1) / cos(2) - sin(1) "
      "* cos(2) + sqrt(3) ^ tan(0.5) + 123 + sin(-x) *55";
  expected_result = OK;
  actual_result = validation(str2);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

Suite *validation_suite(void) {
  Suite *s;
  TCase *tc_validation;
  s = suite_create("\n validation");
  tc_validation = tcase_create("validation");
  tcase_add_test(tc_validation, validation_test_1);
  tcase_add_test(tc_validation, validation_test_2);
  tcase_add_test(tc_validation, validation_test_3);
  tcase_add_test(tc_validation, validation_test_4);
  tcase_add_test(tc_validation, validation_test_5);
  tcase_add_test(tc_validation, validation_test_6);
  tcase_add_test(tc_validation, validation_test_7);
  tcase_add_test(tc_validation, validation_test_8);
  tcase_add_test(tc_validation, validation_test_9);
  suite_add_tcase(s, tc_validation);
  return s;
}

START_TEST(calculate_test_1) {
  char str1[256] = "(sin(2)+cos(3)) * sqrt(5)";
  int expected_result = OK;
  int actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 0), -0.1804396614654603, 1e-7);

  strcpy(str1, "ln(10) - sin(2) / sqrt(3)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 0), 1.7776019788428044, 1e-7);

  strcpy(str1, "tan(4) * cos(5) ^ sin(6)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 0), 1.646407308, 1e-7);

  strcpy(str1, "acos(0.5) + atan(0.8) * log(2)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 0), 1.250314814, 1e-7);

  strcpy(str1, "sqrt(9) + ln(4) - tan(1) / cos(2)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 0), 8.128741949036312, 1e-7);

  strcpy(str1, "sin(1) * cos(2) + sqrt(x) ^ tan(0.5)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 3), 0.9998011863733898, 1e-7);

  strcpy(str1, "2 / sqrt(123)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 0), 0.18033392693348646, 1e-7);

  strcpy(str1, "10 mod 3 + atan(0.6) - log(2)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 0), 1.239389505, 1e-7);

  strcpy(str1, "(sin(1) + cos(2) / sqrt(3)) * ln(4)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 0), 0.8334519488395, 1e-7);

  strcpy(str1, "sqrt(16) - tan(1) * acos(0.2)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 0), 1.8672260480493925, 1e-7);

  strcpy(str1, "x");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 123), 123.0, 1e-7);

  strcpy(str1, "x ^ x");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 2), 4, 1e-7);

  strcpy(str1, "x - asin(0.5)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 1), 0.4764012244017, 1e-7);

  strcpy(str1, "5+10+97+0 * log(12)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 1), 112, 1e-7);

  strcpy(str1, "2^2^3");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 1), 64, 1e-7);

  strcpy(str1, "2^(2^3)");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 1), 256, 1e-7);

  strcpy(str1, "acos(15)+asin(30)/(atan(2)*sqrt(9))");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_nan(calculate(str1, 1));

  strcpy(str1, "cos(3-1)/sin(5)*tan(1)^1");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 1), 0.675872240, 1e-7);

  strcpy(str1,
         "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
         "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 1), -30.0721649, 1e-7);

  strcpy(str1, "ln(10)-(-log(2))");
  expected_result = OK;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
  ck_assert_double_eq_tol(calculate(str1, 1), 2.603615089, 1e-7);

  strcpy(str1, "(cos(()))");
  expected_result = ERROR;
  actual_result = validation(str1);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

Suite *calculate_suite(void) {
  Suite *s;
  TCase *tc_calculate;
  s = suite_create("\n calculate");
  tc_calculate = tcase_create("calculate");
  tcase_add_test(tc_calculate, calculate_test_1);
  suite_add_tcase(s, tc_calculate);
  return s;
}

void smart_calc_testing(SRunner **sr) {
  *sr = srunner_create(validation_suite());
  srunner_add_suite(*sr, calculate_suite());
}

int main(void) {
  int number_failed;
  SRunner *sr = NULL;
  smart_calc_testing(&sr);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
