#include "../s21_matrix.h"

int s21_check_matrix(matrix_t *A) {
  /*
    function checks matrix A
    returns MATRIX_OP_OK if matrix is correct
    returns MATRIX_INCORRECT and removes matrix if its size is incorrect
    or pointer to matrix is NULL or pointers to rows are NULL
  */
  int status = MATRIX_OP_OK;
  if (A == NULL || A->rows <= 0 || A->columns <= 0 || A->matrix == NULL) {
    status = MATRIX_INCORRECT;
  } else {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] == NULL) {
        status = MATRIX_INCORRECT;
      }
    }
  }
  return status;
}