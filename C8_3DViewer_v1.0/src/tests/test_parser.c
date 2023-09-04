#include "test_viewer.h"

START_TEST(error_check_1) {
  data_t data = {0};
  s21_init_data(&data);
  int status = s21_parser("tests/test_data/non_exist.obj", &data);
  ck_assert_int_eq(status, ERROR_FILE);
}
END_TEST

START_TEST(error_check_2) {
  int status = s21_parser("tests/test_data/cube.obj", NULL);
  ck_assert_int_eq(status, ERROR_DATA);
}
END_TEST

START_TEST(models_1) {
  data_t data = {0};
  int status = s21_parser("tests/test_data/cube.obj", &data);
  ck_assert_int_eq(status, OK);
  matrix_t model;
  s21_create_matrix(8, 3, &model);
  model.matrix[0][0] = 1.0;
  model.matrix[0][1] = -1.0;
  model.matrix[0][2] = -1.0;
  model.matrix[1][0] = 1.0;
  model.matrix[1][1] = -1.0;
  model.matrix[1][2] = 1.0;
  model.matrix[2][0] = -1.0;
  model.matrix[2][1] = -1.0;
  model.matrix[2][2] = 1.0;
  model.matrix[3][0] = -1.0;
  model.matrix[3][1] = -1.0;
  model.matrix[3][2] = -1.0;
  model.matrix[4][0] = 1.0;
  model.matrix[4][1] = 1.0;
  model.matrix[4][2] = -1.0;
  model.matrix[5][0] = 1.0;
  model.matrix[5][1] = 1.0;
  model.matrix[5][2] = 1.0;
  model.matrix[6][0] = -1.0;
  model.matrix[6][1] = 1.0;
  model.matrix[6][2] = 1.0;
  model.matrix[7][0] = -1.0;
  model.matrix[7][1] = 1.0;
  model.matrix[7][2] = -1.0;

  for (int r = 0; r < model.rows; r++) {
    for (int c = 0; c < model.columns; c++) {
      ck_assert_double_eq_tol(model.matrix[r][c], data.coordinates.matrix[r][c],
                              1.0e-6);
    }
  }
  polygon_t *temp = (polygon_t *)calloc(12, sizeof(polygon_t));
  for (int i = 0; i < 12; i++) {
    temp[i].vertexes = (int *)calloc(3, sizeof(int));
    temp[i].numbers_of_vertexes_in_facets = 3;
  }

  temp[0].vertexes[0] = 2;
  temp[0].vertexes[1] = 3;
  temp[0].vertexes[2] = 4;
  temp[0].numbers_of_vertexes_in_facets = 3;

  temp[1].vertexes[0] = 8;
  temp[1].vertexes[1] = 7;
  temp[1].vertexes[2] = 6;
  temp[1].numbers_of_vertexes_in_facets = 3;

  temp[2].vertexes[0] = 5;
  temp[2].vertexes[1] = 6;
  temp[2].vertexes[2] = 2;
  temp[2].numbers_of_vertexes_in_facets = 3;

  temp[3].vertexes[0] = 6;
  temp[3].vertexes[1] = 7;
  temp[3].vertexes[2] = 3;
  temp[3].numbers_of_vertexes_in_facets = 3;

  temp[4].vertexes[0] = 3;
  temp[4].vertexes[1] = 7;
  temp[4].vertexes[2] = 8;
  temp[4].numbers_of_vertexes_in_facets = 3;

  temp[5].vertexes[0] = 1;
  temp[5].vertexes[1] = 4;
  temp[5].vertexes[2] = 8;
  temp[5].numbers_of_vertexes_in_facets = 3;

  temp[6].vertexes[0] = 1;
  temp[6].vertexes[1] = 2;
  temp[6].vertexes[2] = 4;
  temp[6].numbers_of_vertexes_in_facets = 3;

  temp[7].vertexes[0] = 5;
  temp[7].vertexes[1] = 8;
  temp[7].vertexes[2] = 6;
  temp[7].numbers_of_vertexes_in_facets = 3;

  temp[8].vertexes[0] = 1;
  temp[8].vertexes[1] = 5;
  temp[8].vertexes[2] = 2;
  temp[8].numbers_of_vertexes_in_facets = 3;

  temp[9].vertexes[0] = 2;
  temp[9].vertexes[1] = 6;
  temp[9].vertexes[2] = 3;
  temp[9].numbers_of_vertexes_in_facets = 3;

  temp[10].vertexes[0] = 4;
  temp[10].vertexes[1] = 3;
  temp[10].vertexes[2] = 8;
  temp[10].numbers_of_vertexes_in_facets = 3;

  temp[11].vertexes[0] = 5;
  temp[11].vertexes[1] = 1;
  temp[11].vertexes[2] = 8;
  temp[11].numbers_of_vertexes_in_facets = 3;

  for (int n = 0; n < data.amount_of_facets; n++) {
    ck_assert_int_eq(temp[n].numbers_of_vertexes_in_facets,
                     data.polygons[n].numbers_of_vertexes_in_facets);
    for (int i = 0; i < data.polygons[n].numbers_of_vertexes_in_facets; i++) {
      ck_assert_int_eq(temp[n].vertexes[i], data.polygons[n].vertexes[i]);
    }
  }

  ck_assert_double_eq(data.min_max[0], -1.0);
  ck_assert_double_eq(data.min_max[1], 1.0);
  ck_assert_double_eq(data.min_max[2], -1.0);
  ck_assert_double_eq(data.min_max[3], 1.0);
  ck_assert_double_eq(data.min_max[4], -1.0);
  ck_assert_double_eq(data.min_max[5], 1.0);

  ck_assert_int_eq(data.amount_of_vertexes, 8);
  ck_assert_int_eq(data.amount_of_facets, 12);

  s21_remove_matrix(&model);
  s21_remove_polygon(&temp, 12);
  s21_remove_data(&data);
}
END_TEST

Suite *test_file(void) {
  Suite *s = suite_create("ERRORS_CHECK");
  TCase *test_case = tcase_create("ERRORS_CHECK");

  tcase_add_test(test_case, error_check_1);
  tcase_add_test(test_case, error_check_2);

  suite_add_tcase(s, test_case);
  return s;
}

Suite *test_model(void) {
  Suite *s = suite_create("MODEL");
  TCase *test_case = tcase_create("MODEL");

  tcase_add_test(test_case, models_1);

  suite_add_tcase(s, test_case);
  return s;
}
