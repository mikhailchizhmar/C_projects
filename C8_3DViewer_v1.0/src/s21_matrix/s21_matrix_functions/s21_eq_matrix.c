#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  /*
    function compares two matrices
    returns 1 if matrices are equal
    returns 0 if matrices are not equal or incorrect
    (matrix A or matrix B is NULL or A and B are not the same size)
  */
  int status = 1;
  double eps = 1e-6;
  if (s21_check_matrix(A) != MATRIX_OP_OK || s21_check_matrix(B) != MATRIX_OP_OK ||
      A->rows != B->rows || A->columns != B->columns) {
    status = 0;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((A->matrix[i][j] - B->matrix[i][j]) > eps ||
            (A->matrix[i][j] - B->matrix[i][j]) < -eps) {
          // double a = 0, b = 0;
          // a = A->matrix[i][j];
          // b = B->matrix[i][j];
          status = 0;
        }
      }
    }
  }
  return status;
}
