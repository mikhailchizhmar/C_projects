#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  /*
    function calculates inverse of matrix A
    returns MATRIX_OP_OK if operation was successful
    returns MATRIX_INCORRECT if input matrix or result matrix are incorrect
    returns MATRIX_OP_ERR if matrix is not square or determinant of matrix A
    is 0
  */
  int status = MATRIX_OP_OK;
  if (s21_check_matrix(A) != MATRIX_OP_OK) {
    status = MATRIX_INCORRECT;
  } else if (A->rows != A->columns) {
    status = MATRIX_OP_ERR;
  }

  if (status == MATRIX_OP_OK) {
    double det = 0;
    status = s21_determinant(A, &det);
    if (status != MATRIX_OP_OK || det == 0 || det != det) {  // NaN
      status = MATRIX_OP_ERR;
    } else {
      matrix_t cofactors, cofactors_transpose;
      double multiplier = 1;
      multiplier = 1. / det;
      // s21_create_matrix(A->rows, A->columns, &cofactors);
      // s21_create_matrix(A->rows, A->columns, &cofactors_transpose);
      status = s21_calc_complements(A, &cofactors);
      if (status == MATRIX_OP_OK) {
        status = s21_transpose(&cofactors, &cofactors_transpose);
        s21_remove_matrix(&cofactors);
      }
      if (status == MATRIX_OP_OK) {
        status = s21_mult_number(&cofactors_transpose, multiplier, result);
        s21_remove_matrix(&cofactors_transpose);
      }
    }
  }
  return status;
}
