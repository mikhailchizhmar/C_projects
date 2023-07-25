#include "my_matrix.h"

int my_create_matrix(int rows, int columns, matrix_t *result) {
  int output = OK;
  if (rows < 1 || columns < 1 || result == NULL) {
    output = INCORRECT_MATRIX;
    result->rows = rows;
    result->columns = columns;
    result->matrix = NULL;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)malloc(rows * sizeof(double *));

    for (int i = 0; i < rows; i++)
      result->matrix[i] = (double *)malloc(columns * sizeof(double));
  }
  return output;
}

void my_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
  free(A->matrix);
}

int my_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns || !validMatrix(A) ||
      !validMatrix(B))
    result = FAILURE;

  if (result) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) result = FAILURE;
      }
    }
  }
  return result;
}

int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int output = OK;
  if (!validMatrix(A) || !validMatrix(B)) {
    output = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns)
    output = CALCULATION_ERROR;

  if (output == OK) {
    my_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  return output;
}

int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int output = OK;
  if (!validMatrix(A) || !validMatrix(B)) {
    output = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns)
    output = CALCULATION_ERROR;

  if (output == OK) {
    my_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return output;
}

int my_mult_number(matrix_t *A, double number, matrix_t *result) {
  int output = OK;
  if (!validMatrix(A))
    output = INCORRECT_MATRIX;
  else {
    my_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return output;
}

int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int output = OK;
  if (!validMatrix(A) || !validMatrix(B)) {
    output = INCORRECT_MATRIX;
  } else if (A->columns != B->rows)
    output = CALCULATION_ERROR;

  if (output == OK) {
    my_create_matrix(A->rows, B->columns, result);
    my_fill(result, 0);  //  мб надо будет удалить
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return output;
}

int my_transpose(matrix_t *A, matrix_t *result) {
  int output = OK;
  if (!validMatrix(A)) output = INCORRECT_MATRIX;

  if (output == OK) {
    my_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return output;
}

int my_determinant(matrix_t *A, double *result) {
  int output = OK;
  if (!validMatrix(A)) {
    output = INCORRECT_MATRIX;
  } else if (A->rows != A->columns)
    output = CALCULATION_ERROR;

  if (output == OK) {
    *result = 0.0;
    if (A->rows == 1) *result = A->matrix[0][0];
    if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    }
    if (A->rows > 2) {
      for (int i = 0; i < A->rows; i++) {
        matrix_t smaller_matrix;
        double temp_det = 0.0;
        delete_row_and_column(A, i, 0, &smaller_matrix);
        my_determinant(&smaller_matrix, &temp_det);
        *result += A->matrix[i][0] * pow(-1, i) * temp_det;
        my_remove_matrix(&smaller_matrix);
      }
    }
  }
  return output;
}

int my_calc_complements(matrix_t *A, matrix_t *result) {
  int output = OK;
  if (!validMatrix(A)) {
    output = INCORRECT_MATRIX;
  } else if (A->rows != A->columns)
    output = CALCULATION_ERROR;

  if (output == OK) {
    my_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t smaller_matrix;
        double temp_det = 0.0;
        delete_row_and_column(A, i, j, &smaller_matrix);
        my_determinant(&smaller_matrix, &temp_det);
        result->matrix[i][j] = pow(-1, i + j) * temp_det;
        my_remove_matrix(&smaller_matrix);
      }
    }
  }
  return output;
}

int my_inverse_matrix(matrix_t *A, matrix_t *result) {
  int output = OK;
  double det = 0.0;
  my_determinant(A, &det);
  if (!validMatrix(A)) {
    output = INCORRECT_MATRIX;
  } else if (A->rows != A->columns || det == 0)
    output = CALCULATION_ERROR;

  if (output == OK) {
    matrix_t support_matrix;
    my_calc_complements(A, result);
    my_transpose(result, &support_matrix);
    my_remove_matrix(result);
    my_mult_number(&support_matrix, 1 / det, result);
    my_remove_matrix(&support_matrix);
  }
  return output;
}
