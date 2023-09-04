#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  /*
    function multiplies two matrices
    returns MATRIX_OP_OK if operation was successful
    returns MATRIX_INCORRECT if input matrices or result matrix are incorrect
    returns MATRIX_OP_ERR if matrix multiplication is impossible
                  (number of columns in A is not equal to number of rows in B
                  or size of result matrix is incorrect)
  */
  int status = MATRIX_OP_OK;
  if (s21_check_matrix(A) != MATRIX_OP_OK || s21_check_matrix(B) != MATRIX_OP_OK) {
    status = MATRIX_INCORRECT;
  } else if (A->columns != B->rows) {
    status = MATRIX_OP_ERR;
  } else {
    status = s21_create_matrix(A->rows, B->columns, result);
  }
  if (status == MATRIX_OP_OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
        // if (result->matrix[i][j] != result->matrix[i][j]) {  // NaN
        //   status = MATRIX_OP_ERR;
        // }
      }
    }
  }
  return status;
}