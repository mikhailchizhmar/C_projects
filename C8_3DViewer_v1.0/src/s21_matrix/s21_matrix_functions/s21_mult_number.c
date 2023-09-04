#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  /*
    function multiplies matrix by number
  */
  int status = MATRIX_OP_OK;
  if (s21_check_matrix(A) != MATRIX_OP_OK) {
    status = MATRIX_INCORRECT;
  } else if (number != number) {  // NaN
    status = MATRIX_OP_ERR;
  } else {
    status = s21_create_matrix(A->rows, A->columns, result);
  }
  if (status == MATRIX_OP_OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
        // if (result->matrix[i][j] != result->matrix[i][j]) {  // NaN
        //   status = MATRIX_OP_ERR;
        // }
      }
    }
  }
  return status;
}