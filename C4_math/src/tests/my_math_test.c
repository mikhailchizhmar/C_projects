#include "../my_math.h"
#include "my_math_test.h"

START_TEST(test_abs_normal) { ck_assert_int_eq(abs(12), my_abs(12)); }
START_TEST(test_abs_negative) { ck_assert_int_eq(abs(-12), my_abs(-12)); }
START_TEST(test_abs_zero) { ck_assert_int_eq(abs(0), my_abs(0)); }

START_TEST(test_acos_normal) { ck_assert_int_eq(acos(1), my_acos(1)); }
START_TEST(test_acos_negative) { ck_assert_int_eq(acos(-1), my_acos(-1)); }
START_TEST(test_acos_zero) { ck_assert_int_eq(acos(0), my_acos(0)); }

START_TEST(test_fabs_normal) {
  ck_assert_int_eq(fabs(12.12345), my_fabs(12.12345));
}
END_TEST
START_TEST(test_fabs_zero) { ck_assert_int_eq(fabs(0.), my_abs(0.)); }
END_TEST
START_TEST(test_fabs_negative) {
  ck_assert_int_eq(fabs(-12.12345), my_fabs(-12.12345));
}
END_TEST

START_TEST(test_fmod_normal) {
  ck_assert_int_eq(fmod(12.12345, 3.2), my_fmod(12.12345, 3.2));
}
END_TEST
START_TEST(test_fmod_negative) {
  ck_assert_int_eq(fmod(-12.12345, 3.2), my_fmod(-12.12345, 3.2));
}
END_TEST
START_TEST(test_fmod_zero) {
  ck_assert_int_eq(fmod(12.12345, 0), my_fmod(12.12345, 0));
}
END_TEST

START_TEST(test_floor_normal) {
  ck_assert_int_eq(floor(12.12345), my_floor(12.12345));
}
END_TEST
START_TEST(test_floor_negative) {
  ck_assert_int_eq(floor(-12.12345), my_floor(-12.12345));
}
END_TEST

START_TEST(test_ceil_normal) {
  ck_assert_int_eq(ceil(12.12345), my_ceil(12.12345));
}
END_TEST
START_TEST(test_ceil_negative) {
  ck_assert_int_eq(ceil(-12.12345), my_ceil(-12.12345));
}
END_TEST
START_TEST(test_ceil_zero) { ck_assert_int_eq(ceil(0), my_ceil(0)); }
END_TEST

START_TEST(test_cos_zero) { ck_assert_int_eq(cos(0), my_cos(0)); }
END_TEST
START_TEST(test_cos_normal) { ck_assert_int_eq(cos(1), my_cos(1)); }
END_TEST
START_TEST(test_cos_negative) { ck_assert_int_eq(cos(-1), my_cos(-1)); }
END_TEST

START_TEST(test_asin_one) { ck_assert_int_eq(asin(1), my_asin(1)); }
END_TEST
START_TEST(test_asin_zero) { ck_assert_int_eq(asin(0), my_asin(0)); }
END_TEST
START_TEST(test_asin_negative) { ck_assert_int_eq(asin(-1), my_asin(-1)); }
END_TEST

START_TEST(test_atan_normal) { ck_assert_int_eq(atan(1), my_atan(1)); }
END_TEST
START_TEST(test_atan_zero) { ck_assert_int_eq(atan(0), my_atan(0)); }
END_TEST
START_TEST(test_atan_negative) { ck_assert_int_eq(atan(-1), my_atan(-1)); }
END_TEST

START_TEST(test_exp_normal) { ck_assert_int_eq(exp(1.5), my_exp(1.5)); }
END_TEST
START_TEST(test_exp_negative) { ck_assert_int_eq(exp(-1.5), my_exp(-1.5)); }
END_TEST
START_TEST(test_exp_zero) { ck_assert_int_eq(exp(0), my_exp(0)); }
END_TEST

START_TEST(test_log_normal) { ck_assert_int_eq(log(1.5), my_log(1.5)); }
END_TEST
START_TEST(test_log_negative) { ck_assert_int_eq(log(-1.5), my_log(-1.5)); }
END_TEST
START_TEST(test_log_zero) { ck_assert_int_eq(log(0), my_log(0)); }
END_TEST

START_TEST(test_pow_normal) { ck_assert_int_eq(pow(1.5, 5), my_pow(1.5, 5)); }
END_TEST
START_TEST(test_pow_negative) {
  ck_assert_int_eq(pow(-1.5, 5), my_pow(-1.5, 5));
}
END_TEST
START_TEST(test_pow_zero) { ck_assert_int_eq(pow(0., 5), my_pow(0., 5)); }
END_TEST

START_TEST(test_sin_normal) { ck_assert_int_eq(sin(1.5), my_sin(1.5)); }
END_TEST
START_TEST(test_sin_negative) { ck_assert_int_eq(sin(-1.5), my_sin(-1.5)); }
END_TEST
START_TEST(test_sin_zero) { ck_assert_int_eq(sin(0), my_sin(0)); }
END_TEST

START_TEST(test_sqrt_normal) { ck_assert_int_eq(sqrt(1.5), my_sqrt(1.5)); }
END_TEST
START_TEST(test_sqrt_negative) { ck_assert_int_eq(sqrt(-1.5), my_sqrt(-1.5)); }
END_TEST
START_TEST(test_sqrt_zero) { ck_assert_int_eq(sqrt(0), my_sqrt(0)); }
END_TEST

START_TEST(test_tan_normal) { ck_assert_int_eq(tan(1.5), my_tan(1.5)); }
END_TEST
START_TEST(test_tan_negative) { ck_assert_int_eq(tan(-1.5), my_tan(-1.5)); }
END_TEST
START_TEST(test_tan_zero) { ck_assert_int_eq(tan(0), my_tan(0)); }
END_TEST

Suite *my_fabs_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_fabs");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_fabs_normal);
  tcase_add_test(tc_core, test_fabs_zero);
  tcase_add_test(tc_core, test_fabs_negative);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_fmod_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_fmod");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_fmod_normal);
  tcase_add_test(tc_core, test_fmod_negative);
  tcase_add_test(tc_core, test_fmod_zero);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_floor_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_floor");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_floor_normal);
  tcase_add_test(tc_core, test_floor_negative);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_ceil_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_ceil");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_ceil_normal);
  tcase_add_test(tc_core, test_ceil_negative);
  tcase_add_test(tc_core, test_ceil_zero);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_cos_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_cos");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_cos_normal);
  tcase_add_test(tc_core, test_cos_negative);
  tcase_add_test(tc_core, test_cos_zero);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_asin_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_asin");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_asin_one);
  tcase_add_test(tc_core, test_asin_zero);
  tcase_add_test(tc_core, test_asin_negative);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_abs_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_abs");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_abs_normal);
  tcase_add_test(tc_core, test_abs_negative);
  tcase_add_test(tc_core, test_abs_zero);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_acos_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_acos");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_acos_normal);
  tcase_add_test(tc_core, test_acos_negative);
  tcase_add_test(tc_core, test_acos_zero);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_atan_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_atan");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_atan_normal);
  tcase_add_test(tc_core, test_atan_zero);
  tcase_add_test(tc_core, test_atan_negative);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_exp_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_exp");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_exp_normal);
  tcase_add_test(tc_core, test_exp_negative);
  tcase_add_test(tc_core, test_exp_zero);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_log_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_log");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_log_normal);
  tcase_add_test(tc_core, test_log_zero);
  tcase_add_test(tc_core, test_log_negative);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_pow_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_pow");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_pow_normal);
  tcase_add_test(tc_core, test_pow_zero);
  tcase_add_test(tc_core, test_pow_negative);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_sin_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_sin");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_sin_normal);
  tcase_add_test(tc_core, test_sin_zero);
  tcase_add_test(tc_core, test_sin_negative);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_sqrt_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_sqrt");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_sqrt_normal);
  tcase_add_test(tc_core, test_sqrt_zero);
  tcase_add_test(tc_core, test_sqrt_negative);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *my_tan_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("my_tan");
  tc_core = tcase_create("all_in_one");
  tcase_add_test(tc_core, test_tan_normal);
  tcase_add_test(tc_core, test_tan_zero);
  tcase_add_test(tc_core, test_tan_negative);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;
  // abs testing
  s = my_abs_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // acos testing
  s = my_acos_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // asin testing
  s = my_asin_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // atan testing
  s = my_atan_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // ceil testing
  s = my_ceil_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // cos testing
  s = my_cos_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // exp testing
  s = my_exp_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // fabs testing
  s = my_fabs_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // floor testing
  s = my_floor_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // fmod testing
  s = my_fmod_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // log testing
  s = my_log_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // pow testing
  s = my_pow_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // sin testing
  s = my_sin_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // sqrt testing
  s = my_sqrt_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  // tan testing
  s = my_tan_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

  return 0;
}
