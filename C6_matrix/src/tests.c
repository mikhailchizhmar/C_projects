#include <check.h>

#include "my_matrix.h"

void my_matrix_testing(SRunner **sr);

START_TEST(my_eq_matrix_test_1) {
  matrix_t A, B;
  my_create_matrix(41, 41, &A);
  my_create_matrix(41, 41, &B);
  my_fill(&A, 1);
  my_fill(&B, 1);
  int expected_result = SUCCESS;
  int actual_result = my_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_eq_matrix_test_2) {
  matrix_t A, B;
  my_create_matrix(83, 83, &A);
  my_create_matrix(83, 83, &B);
  my_fill(&A, 7);
  my_fill(&B, 9);
  int expected_result = FAILURE;
  int actual_result = my_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_eq_matrix_test_3) {
  matrix_t A, B;
  my_create_matrix(32, 32, &A);
  my_create_matrix(27, 27, &B);
  my_fill(&A, 42);
  my_fill(&B, 42);
  int expected_result = FAILURE;
  int actual_result = my_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_eq_matrix_test_4) {
  matrix_t A, B;
  my_create_matrix(22, 22, &A);
  my_create_matrix(22, 22, &B);
  my_fill(&A, 13);
  my_fill(&B, 13);
  int expected_result = SUCCESS;
  int actual_result = my_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

Suite *my_eq_matrix_suite(void) {
  Suite *s;
  TCase *tc_my_eq_matrix;
  s = suite_create("\n my_eq_matrix");
  tc_my_eq_matrix = tcase_create("eq_matrix");
  tcase_add_test(tc_my_eq_matrix, my_eq_matrix_test_1);
  tcase_add_test(tc_my_eq_matrix, my_eq_matrix_test_2);
  tcase_add_test(tc_my_eq_matrix, my_eq_matrix_test_3);
  tcase_add_test(tc_my_eq_matrix, my_eq_matrix_test_4);
  suite_add_tcase(s, tc_my_eq_matrix);
  return s;
}

START_TEST(my_sum_matrix_test_1) {
  matrix_t A, B, expected_matrix, actual_matrix;
  int expected_result = OK, actual_result;
  my_create_matrix(4, 4, &A);
  my_create_matrix(4, 4, &B);
  my_fill(&A, 3);
  my_fill(&B, 4);
  my_create_matrix(4, 4, &expected_matrix);
  my_fill(&expected_matrix, 7);
  actual_result = my_sum_matrix(&A, &B, &actual_matrix);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(expected_matrix.matrix[i][j],
                          actual_matrix.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&expected_matrix);
  my_remove_matrix(&actual_matrix);
}
END_TEST

START_TEST(my_sum_matrix_test_2) {
  matrix_t A, B, actual_matrix;
  int expected_result = CALCULATION_ERROR, actual_result;
  my_create_matrix(2, 2, &A);
  my_create_matrix(4, 4, &B);
  actual_result = my_sum_matrix(&A, &B, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_sum_matrix_test_3) {
  matrix_t A, B, actual_matrix;
  int expected_result = INCORRECT_MATRIX, actual_result;
  my_create_matrix(0, 0, &A);
  my_create_matrix(4, 5, &B);
  actual_result = my_sum_matrix(&A, &B, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&B);
}
END_TEST

Suite *my_sum_matrix_suite(void) {
  Suite *s;
  TCase *tc_my_sum_matrix;
  s = suite_create("\n my_sum_matrix");
  tc_my_sum_matrix = tcase_create("sum_matrix");
  tcase_add_test(tc_my_sum_matrix, my_sum_matrix_test_1);
  tcase_add_test(tc_my_sum_matrix, my_sum_matrix_test_2);
  tcase_add_test(tc_my_sum_matrix, my_sum_matrix_test_3);
  suite_add_tcase(s, tc_my_sum_matrix);
  return s;
}

START_TEST(my_sub_matrix_test_1) {
  matrix_t A, B, expected_matrix, actual_matrix;
  int expected_result = OK, actual_result;
  my_create_matrix(4, 4, &A);
  my_create_matrix(4, 4, &B);
  my_fill(&A, 7);
  my_fill(&B, 2);
  my_create_matrix(4, 4, &expected_matrix);
  my_fill(&expected_matrix, 5);
  actual_result = my_sub_matrix(&A, &B, &actual_matrix);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(expected_matrix.matrix[i][j],
                          actual_matrix.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&expected_matrix);
  my_remove_matrix(&actual_matrix);
}
END_TEST

START_TEST(my_sub_matrix_test_2) {
  matrix_t A, B, actual_matrix;
  int expected_result = CALCULATION_ERROR, actual_result;
  my_create_matrix(2, 2, &A);
  my_create_matrix(4, 4, &B);
  actual_result = my_sub_matrix(&A, &B, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_sub_matrix_test_3) {
  matrix_t A, B, actual_matrix;
  int expected_result = INCORRECT_MATRIX, actual_result;
  my_create_matrix(0, 0, &A);
  my_create_matrix(4, 5, &B);
  actual_result = my_sub_matrix(&A, &B, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&B);
}
END_TEST

Suite *my_sub_matrix_suite(void) {
  Suite *s;
  TCase *tc_my_sub_matrix;
  s = suite_create("\n my_sub_matrix");
  tc_my_sub_matrix = tcase_create("sub_matrix");
  tcase_add_test(tc_my_sub_matrix, my_sub_matrix_test_1);
  tcase_add_test(tc_my_sub_matrix, my_sub_matrix_test_2);
  tcase_add_test(tc_my_sub_matrix, my_sub_matrix_test_3);
  suite_add_tcase(s, tc_my_sub_matrix);
  return s;
}

START_TEST(my_mult_number_test_1) {
  matrix_t A, expected_matrix, actual_matrix;
  int expected_result = OK, actual_result;
  my_create_matrix(4, 7, &A);
  my_fill(&A, 3);
  my_create_matrix(4, 7, &expected_matrix);
  my_fill(&expected_matrix, 30);
  actual_result = my_mult_number(&A, 10, &actual_matrix);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 7; j++) {
      ck_assert_double_eq(expected_matrix.matrix[i][j],
                          actual_matrix.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&expected_matrix);
  my_remove_matrix(&actual_matrix);
}
END_TEST

START_TEST(my_mult_number_test_2) {
  matrix_t A, actual_matrix;
  int expected_result = INCORRECT_MATRIX, actual_result;
  my_create_matrix(-3, -5, &A);
  actual_result = my_mult_number(&A, 3, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

Suite *my_mult_number_suite(void) {
  Suite *s;
  TCase *tc_my_mult_number;
  s = suite_create("\n my_mult_number");
  tc_my_mult_number = tcase_create("mult_number");
  tcase_add_test(tc_my_mult_number, my_mult_number_test_1);
  tcase_add_test(tc_my_mult_number, my_mult_number_test_2);
  suite_add_tcase(s, tc_my_mult_number);
  return s;
}

START_TEST(my_mult_matrix_test_1) {
  matrix_t A, B, expected_matrix, actual_matrix;
  int expected_result = OK, actual_result;
  my_create_matrix(2, 4, &A);
  my_create_matrix(4, 3, &B);
  my_fill(&A, 2);
  my_fill(&B, 5);
  my_create_matrix(2, 3, &expected_matrix);
  my_fill(&expected_matrix, 40);
  actual_result = my_mult_matrix(&A, &B, &actual_matrix);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(expected_matrix.matrix[i][j],
                          actual_matrix.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
  my_remove_matrix(&expected_matrix);
  my_remove_matrix(&actual_matrix);
}
END_TEST

START_TEST(my_mult_matrix_test_2) {
  matrix_t A, B, actual_matrix;
  int expected_result = CALCULATION_ERROR, actual_result;
  my_create_matrix(2, 5, &A);
  my_create_matrix(4, 3, &B);
  actual_result = my_mult_matrix(&A, &B, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&B);
}
END_TEST

START_TEST(my_mult_matrix_test_3) {
  matrix_t A, B, actual_matrix;
  int expected_result = INCORRECT_MATRIX, actual_result;
  my_create_matrix(0, 4, &A);
  my_create_matrix(4, 5, &B);
  actual_result = my_mult_matrix(&A, &B, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&B);
}
END_TEST

Suite *my_mult_matrix_suite(void) {
  Suite *s;
  TCase *tc_my_mult_matrix;
  s = suite_create("\n my_mult_matrix");
  tc_my_mult_matrix = tcase_create("mult_matrix");
  tcase_add_test(tc_my_mult_matrix, my_mult_matrix_test_1);
  tcase_add_test(tc_my_mult_matrix, my_mult_matrix_test_2);
  tcase_add_test(tc_my_mult_matrix, my_mult_matrix_test_3);
  suite_add_tcase(s, tc_my_mult_matrix);
  return s;
}

START_TEST(my_transpose_test_1) {
  matrix_t A, expected_matrix, actual_matrix;
  int expected_result = OK, actual_result;
  my_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  my_create_matrix(3, 2, &expected_matrix);
  expected_matrix.matrix[0][0] = 1;
  expected_matrix.matrix[0][1] = 4;

  expected_matrix.matrix[1][0] = 2;
  expected_matrix.matrix[1][1] = 5;

  expected_matrix.matrix[2][0] = 3;
  expected_matrix.matrix[2][1] = 6;

  actual_result = my_transpose(&A, &actual_matrix);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq(expected_matrix.matrix[i][j],
                          actual_matrix.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&expected_matrix);
  my_remove_matrix(&actual_matrix);
}
END_TEST

START_TEST(my_transpose_test_2) {
  matrix_t A, actual_matrix;
  int expected_result = INCORRECT_MATRIX, actual_result;
  my_create_matrix(-3, 5, &A);
  actual_result = my_transpose(&A, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

Suite *my_transpose_suite(void) {
  Suite *s;
  TCase *tc_my_transpose;
  s = suite_create("\n my_transpose");
  tc_my_transpose = tcase_create("transpose");
  tcase_add_test(tc_my_transpose, my_transpose_test_1);
  tcase_add_test(tc_my_transpose, my_transpose_test_2);
  suite_add_tcase(s, tc_my_transpose);
  return s;
}

START_TEST(my_determinant_test_1) {
  matrix_t A;
  int expected_result = OK, actual_result;
  double expected_det = 0, actual_det;
  my_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  actual_result = my_determinant(&A, &actual_det);
  ck_assert_double_eq(expected_det, actual_det);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(my_determinant_test_2) {
  matrix_t A;
  int expected_result = INCORRECT_MATRIX, actual_result;
  double actual_det;
  my_create_matrix(10, 0, &A);
  actual_result = my_determinant(&A, &actual_det);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(my_determinant_test_3) {
  matrix_t A;
  int expected_result = CALCULATION_ERROR, actual_result;
  double actual_det;
  my_create_matrix(5, 2, &A);
  actual_result = my_determinant(&A, &actual_det);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
}
END_TEST

Suite *my_determinant_suite(void) {
  Suite *s;
  TCase *tc_my_determinant;
  s = suite_create("\n my_determinant");
  tc_my_determinant = tcase_create("determinant");
  tcase_add_test(tc_my_determinant, my_determinant_test_1);
  tcase_add_test(tc_my_determinant, my_determinant_test_2);
  tcase_add_test(tc_my_determinant, my_determinant_test_3);
  suite_add_tcase(s, tc_my_determinant);
  return s;
}

START_TEST(my_calc_complements_test_1) {
  matrix_t A, expected_matrix, actual_matrix;
  int expected_result = OK, actual_result;
  my_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  my_create_matrix(3, 3, &expected_matrix);
  expected_matrix.matrix[0][0] = 0;
  expected_matrix.matrix[0][1] = 10;
  expected_matrix.matrix[0][2] = -20;

  expected_matrix.matrix[1][0] = 4;
  expected_matrix.matrix[1][1] = -14;
  expected_matrix.matrix[1][2] = 8;

  expected_matrix.matrix[2][0] = -8;
  expected_matrix.matrix[2][1] = -2;
  expected_matrix.matrix[2][2] = 4;

  actual_result = my_calc_complements(&A, &actual_matrix);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(expected_matrix.matrix[i][j],
                          actual_matrix.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&expected_matrix);
  my_remove_matrix(&actual_matrix);
}
END_TEST

START_TEST(my_calc_complements_test_2) {
  matrix_t A, actual_matrix;
  int expected_result = INCORRECT_MATRIX, actual_result;
  my_create_matrix(10, 0, &A);
  actual_result = my_calc_complements(&A, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(my_calc_complements_test_3) {
  matrix_t A, actual_matrix;
  int expected_result = CALCULATION_ERROR, actual_result;
  my_create_matrix(2, 6, &A);
  actual_result = my_calc_complements(&A, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
}
END_TEST

Suite *my_calc_complements_suite(void) {
  Suite *s;
  TCase *tc_my_calc_complements;
  s = suite_create("\n my_calc_complements");
  tc_my_calc_complements = tcase_create("calc_complements");
  tcase_add_test(tc_my_calc_complements, my_calc_complements_test_1);
  tcase_add_test(tc_my_calc_complements, my_calc_complements_test_2);
  tcase_add_test(tc_my_calc_complements, my_calc_complements_test_3);
  suite_add_tcase(s, tc_my_calc_complements);
  return s;
}

START_TEST(my_inverse_matrix_test_1) {
  matrix_t A, expected_matrix, actual_matrix;
  int expected_result = OK, actual_result;
  my_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;

  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  my_create_matrix(3, 3, &expected_matrix);
  expected_matrix.matrix[0][0] = 1;
  expected_matrix.matrix[0][1] = -1;
  expected_matrix.matrix[0][2] = 1;

  expected_matrix.matrix[1][0] = -38;
  expected_matrix.matrix[1][1] = 41;
  expected_matrix.matrix[1][2] = -34;

  expected_matrix.matrix[2][0] = 27;
  expected_matrix.matrix[2][1] = -29;
  expected_matrix.matrix[2][2] = 24;

  actual_result = my_inverse_matrix(&A, &actual_matrix);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(expected_matrix.matrix[i][j],
                          actual_matrix.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
  my_remove_matrix(&expected_matrix);
  my_remove_matrix(&actual_matrix);
}
END_TEST

START_TEST(my_inverse_matrix_test_2) {
  matrix_t A, actual_matrix;
  int expected_result = INCORRECT_MATRIX, actual_result;
  my_create_matrix(20, 0, &A);
  actual_result = my_inverse_matrix(&A, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
}
END_TEST

START_TEST(my_inverse_matrix_test_3) {
  matrix_t A, actual_matrix;
  int expected_result = CALCULATION_ERROR, actual_result;
  my_create_matrix(2, 6, &A);
  actual_result = my_inverse_matrix(&A, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
}
END_TEST

START_TEST(my_inverse_matrix_test_4) {
  matrix_t A, actual_matrix;
  int expected_result = CALCULATION_ERROR, actual_result;
  my_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  actual_result = my_inverse_matrix(&A, &actual_matrix);
  ck_assert_uint_eq(expected_result, actual_result);
  my_remove_matrix(&A);
}
END_TEST

Suite *my_inverse_matrix_suite(void) {
  Suite *s;
  TCase *tc_my_inverse_matrix;
  s = suite_create("\n my_inverse_matrix");
  tc_my_inverse_matrix = tcase_create("inverse_matrix");
  tcase_add_test(tc_my_inverse_matrix, my_inverse_matrix_test_1);
  tcase_add_test(tc_my_inverse_matrix, my_inverse_matrix_test_2);
  tcase_add_test(tc_my_inverse_matrix, my_inverse_matrix_test_3);
  tcase_add_test(tc_my_inverse_matrix, my_inverse_matrix_test_4);
  suite_add_tcase(s, tc_my_inverse_matrix);
  return s;
}

void my_matrix_testing(SRunner **sr) {
  *sr = srunner_create(my_eq_matrix_suite());
  srunner_add_suite(*sr, my_sum_matrix_suite());
  srunner_add_suite(*sr, my_sub_matrix_suite());
  srunner_add_suite(*sr, my_mult_number_suite());
  srunner_add_suite(*sr, my_mult_matrix_suite());
  srunner_add_suite(*sr, my_transpose_suite());
  srunner_add_suite(*sr, my_determinant_suite());
  srunner_add_suite(*sr, my_calc_complements_suite());
  srunner_add_suite(*sr, my_inverse_matrix_suite());
}

int main(void) {
  int number_failed;
  SRunner *sr = NULL;
  my_matrix_testing(&sr);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}