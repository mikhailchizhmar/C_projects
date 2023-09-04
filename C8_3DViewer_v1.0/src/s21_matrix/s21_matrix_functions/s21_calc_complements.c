#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  /*
    function calculates the matrix of cofactors of A
    returns MATRIX_OP_OK if operation was successful
    returns MATRIX_INCORRECT if input matrix or result matrix are incorrect
    returns MATRIX_OP_ERR if matrix transposition is impossible
                            (size of result matrix is incorrect)
  */
  int status = MATRIX_OP_OK;
  if (s21_check_matrix(A) != MATRIX_OP_OK) {
    status = MATRIX_INCORRECT;
  } else if (A->rows != A->columns || A->rows == 1) {
    status = MATRIX_OP_ERR;
  } else {
    status = s21_create_matrix(A->rows, A->columns, result);
  }
  if (status == MATRIX_OP_OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        int sign = 1;
        matrix_t temp;
        double temp_det = 0;
        sign = (i + j) % 2 == 0 ? 1 : -1;
        status =
            (status == MATRIX_OP_OK) ? s21_del_row_and_column(A, i, j, &temp) : status;
        if (status == MATRIX_OP_OK) {
          status = s21_determinant(&temp, &temp_det);
          s21_remove_matrix(&temp);
        }
        if (status != MATRIX_OP_OK || temp_det != temp_det) {  // NaN
          status = MATRIX_OP_ERR;
        } else {
          result->matrix[i][j] = sign * temp_det;
        }
      }
    }
    if (status != MATRIX_OP_OK) {
      s21_remove_matrix(result);
    }
  }
  return status;
}