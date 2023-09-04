#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  /*
    function calculates determinant of matrix A
    returns MATRIX_OP_OK if operation was successful
    returns MATRIX_INCORRECT if input matrix is incorrect
    returns MATRIX_OP_ERR if matrix is not square,
        result pointer is NULL or determinant is NAN
  */
  int status = MATRIX_OP_OK;
  if (s21_check_matrix(A) != MATRIX_OP_OK) {
    status = MATRIX_INCORRECT;
  } else if (A->rows != A->columns || result == NULL) {
    status = MATRIX_OP_ERR;
  } else {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      *result = 0;
      for (int i = 0; i < A->rows; i++) {
        matrix_t temp;
        double temp_det = 0;
        int sign = 1;
        sign = (i % 2 == 0) ? 1 : -1;
        status =
            (status == MATRIX_OP_OK) ? s21_del_row_and_column(A, 0, i, &temp) : status;
        if (status == MATRIX_OP_OK) {
          status = s21_determinant(&temp, &temp_det);
          s21_remove_matrix(&temp);
        }
        if (status != MATRIX_OP_OK || temp_det != temp_det) {  // NaN
          status = MATRIX_OP_ERR;
        } else {
          *result = *result + (A->matrix[0][i] * temp_det) * sign;
        }
      }
    }
  }
  if (status == MATRIX_OP_OK) {
    if (*result != *result) {  // NaN
      status = MATRIX_OP_ERR;
    }
  }
  return status;
}
