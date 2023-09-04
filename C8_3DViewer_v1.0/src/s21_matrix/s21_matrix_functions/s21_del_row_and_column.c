#include "../s21_matrix.h"

int s21_del_row_and_column(matrix_t *A, int row, int column, matrix_t *result) {
  /*
    function puts into the result matrix all rows and columns of matrix A except
    the row and column with the given indexes
  */
  int status = MATRIX_OP_OK;
  if (s21_check_matrix(A) != MATRIX_OP_OK) {
    status = MATRIX_INCORRECT;
  } else if (A->rows <= row || A->columns <= column) {
    status = MATRIX_OP_ERR;
  } else {
    status = s21_create_matrix(A->rows - 1, A->columns - 1, result);
  }
  if (status == MATRIX_OP_OK) {
    int m = 0, n = 0;
    for (int i = 0; i < A->rows; i++) {
      n = 0;
      if (i != row) {
        for (int j = 0; j < A->columns; j++) {
          if (j != column) {
            result->matrix[m][n] = A->matrix[i][j];
            n++;
          }
        }
        m++;
      }
    }
  }
  return status;
}
