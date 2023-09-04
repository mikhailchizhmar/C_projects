#include "../s21_matrix.h"

int s21_sum_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int sign) {
  int status = MATRIX_OP_OK;
  if (s21_check_matrix(A) != MATRIX_OP_OK || s21_check_matrix(B) != MATRIX_OP_OK) {
    status = MATRIX_INCORRECT;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    status = MATRIX_OP_ERR;
  } else {
    status = s21_create_matrix(A->rows, A->columns, result);
  }
  if (status == MATRIX_OP_OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (sign == 1) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        } else {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
        // if (result->matrix[i][j] != result->matrix[i][j]) {  // NaN
        //   status = MATRIX_OP_ERR;
        // }
      }
    }
  }
  return status;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = MATRIX_OP_OK;
  status = s21_sum_sub_matrix(A, B, result, 0);
  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = MATRIX_OP_OK;
  status = s21_sum_sub_matrix(A, B, result, 1);
  return status;
}
