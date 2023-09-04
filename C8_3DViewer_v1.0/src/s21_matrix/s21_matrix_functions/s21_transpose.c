#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  /*
    function transposes matrix A
    returns MATRIX_OP_OK if operation was successful
    returns MATRIX_INCORRECT if input matrix or result matrix are incorrect
    returns MATRIX_OP_ERR if matrix transposition is impossible
                            (size of result matrix is incorrect)
                            or one or more values of the result matrix are NAN
  */
  int status = MATRIX_OP_OK;

  if (s21_check_matrix(A) != MATRIX_OP_OK) {
    status = MATRIX_INCORRECT;
  } else {
    status = s21_create_matrix(A->columns, A->rows, result);
  }
  if (status == MATRIX_OP_OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
        // if (result->matrix[j][i] != result->matrix[j][i]) {  // NaN
        //   status = MATRIX_OP_ERR;
        // }
      }
    }
  }
  return status;
}
