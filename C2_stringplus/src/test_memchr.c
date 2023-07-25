#include "test_my.h"

START_TEST(memchr_1) {
  char str[] = "Hello, world!";
  int ch = ' ';
  my_size_t len = 0;
  len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_2) {
  char str[] = "Hello, world!";
  int ch = 101;
  my_size_t len = 0;
  len = strlen(str);
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_3) {
  char str[] = "Hello, world!";
  int ch = '1';
  my_size_t len = 0;
  len = strlen(str);
  ck_assert_ptr_null(my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_4) {
  char str[] = "Hello, world!";
  int ch = 65;
  my_size_t len = 0;
  len = strlen(str);
  ck_assert_ptr_null(my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_5) {
  char str[] = "Hello, world!";
  int ch = 'l';
  my_size_t len = 10;
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_6) {
  char str[] = "Hello, world!";
  int ch = 'w';
  my_size_t len = 5;
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_7) {
  char str[] = "69917020";
  int ch = '3';
  my_size_t len = 0;
  len = strlen(str);
  ck_assert_ptr_null(my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_8) {
  char str[] = "69917020";
  int ch = '6';
  my_size_t len = 0;
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_9) {
  char str[] = "69917020";
  int ch = 'g';
  my_size_t len = 0;
  len = strlen(str);
  ck_assert_ptr_null(my_memchr(str, ch, len));
}
END_TEST

START_TEST(memchr_10) {
  char str[] = "69917020";
  int ch = '\0';
  my_size_t len = 9;
  ck_assert_ptr_eq(memchr(str, ch, len), my_memchr(str, ch, len));
}
END_TEST

Suite *test_memchr(void) {
  Suite *s = suite_create("\033[34m-=my_MEMCHR=-\033[0m");
  TCase *tc = tcase_create("memchr_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, memchr_1);
  tcase_add_test(tc, memchr_2);
  tcase_add_test(tc, memchr_3);
  tcase_add_test(tc, memchr_4);
  tcase_add_test(tc, memchr_5);
  tcase_add_test(tc, memchr_6);
  tcase_add_test(tc, memchr_7);
  tcase_add_test(tc, memchr_8);
  tcase_add_test(tc, memchr_9);
  tcase_add_test(tc, memchr_10);

  suite_add_tcase(s, tc);
  return s;
}
