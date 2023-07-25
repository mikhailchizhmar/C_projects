#include "my_matrix.h"

int main() {
  matrix_t A, result;
  // double res;
  //  int expected_result = INCORRECT_MATRIX, actual_result;
  my_create_matrix(3, 3, &A);
  input(&A);
  output(A);
  printf("\n%d\n", my_inverse_matrix(&A, &result));
  output(result);
  my_remove_matrix(&A);
  my_remove_matrix(&result);

  return 0;
}