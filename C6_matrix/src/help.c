#include "my_matrix.h"

void input(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      printf("A[%d][%d] = ", i, j);
      scanf("%lf", &A->matrix[i][j]);
    }
  }
}

void output(matrix_t A) {
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      printf("%.7lf ", A.matrix[i][j]);
    }
    printf("\n");
  }
}

int validMatrix(matrix_t *matrix) {
  int result = FAILURE;
  if ((matrix != NULL) && (matrix->matrix != NULL) && (matrix->rows > 0) &&
      (matrix->columns > 0)) {
    result = SUCCESS;
  }
  return result;
}

void my_fill(matrix_t *A, double value) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = value;
    }
  }
}

void delete_row_and_column(matrix_t *A, int row, int column, matrix_t *result) {
  my_create_matrix(A->rows - 1, A->columns - 1, result);
  for (int i = 0, a = 0; i < A->rows; i++) {
    if (i != row) {
      for (int j = 0, b = 0; j < A->rows; j++) {
        if (j != column) {
          result->matrix[a][b] = A->matrix[i][j];
          b++;
        }
      }
      a++;
    }
  }
}
