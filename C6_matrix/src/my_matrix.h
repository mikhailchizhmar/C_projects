#ifndef SRC_MY_MATRIX_H_
#define SRC_MY_MATRIX_H_

#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-7
#define SUCCESS 1
#define FAILURE 0

enum returns { OK, INCORRECT_MATRIX, CALCULATION_ERROR };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int my_create_matrix(int rows, int columns, matrix_t *result);
void my_remove_matrix(matrix_t *A);
int my_eq_matrix(matrix_t *A, matrix_t *B);
int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_mult_number(matrix_t *A, double number, matrix_t *result);
int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_transpose(matrix_t *A, matrix_t *result);
int my_calc_complements(matrix_t *A, matrix_t *result);
int my_determinant(matrix_t *A, double *result);
int my_inverse_matrix(matrix_t *A, matrix_t *result);

void input(matrix_t *A);
void output(matrix_t A);
int validMatrix(matrix_t *matrix);
void my_fill(matrix_t *matrixStruct, double value);
void delete_row_and_column(matrix_t *A, int row, int column, matrix_t *result);

#endif  // SRC_MY_MATRIX_H_