#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = MATRIX_OP_OK;
  if (rows <= 0 || columns <= 0) {
    status = MATRIX_INCORRECT;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
  }
  if (status == MATRIX_OP_OK && result->matrix != NULL) {
    for (int i = 0; (i < rows && status == MATRIX_OP_OK); i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        status = MATRIX_INCORRECT;
        s21_remove_matrix(result);
      }
    }
  } else {
    status = MATRIX_INCORRECT;
  }
  if (status == MATRIX_INCORRECT) {
    result->rows = 0;
    result->columns = 0;
    result->matrix = NULL;
  }
  return status;
}