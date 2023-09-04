#include "s21_viewer.h"

// matrix_t matrix[n_rows][n_cols];
// n_rows = (number of vertexes - 1);
// n_cols = 3: x, y, z coordinates.

int get_min_max(data_t *data) {
  // function finds min and max value of x, y, z coordinates
  // of vertexes in 3D model (data->coordinates.matrix) and puts them
  // into array data->min_max = [x_min, x_max, y_min, y_max, z_min, z_max]
  int status = OK;
  if (data == NULL || data->amount_of_vertexes <= 0 ||
      s21_check_matrix(&(data->coordinates)) != MATRIX_OP_OK) {
    return ERROR;
  }
  data->min_max[0] = data->coordinates.matrix[0][0];
  data->min_max[1] = data->coordinates.matrix[0][0];
  data->min_max[2] = data->coordinates.matrix[0][1];
  data->min_max[3] = data->coordinates.matrix[0][1];
  data->min_max[4] = data->coordinates.matrix[0][2];
  data->min_max[5] = data->coordinates.matrix[0][2];
  for (int vertex = 0; vertex < data->amount_of_vertexes; vertex++) {
    for (int coord = 0; coord < 3; coord++) {
      if (data->min_max[coord * 2] > data->coordinates.matrix[vertex][coord]) {
        data->min_max[coord * 2] = data->coordinates.matrix[vertex][coord];
      }
      if (data->min_max[coord * 2 + 1] <
          data->coordinates.matrix[vertex][coord]) {
        data->min_max[coord * 2 + 1] = data->coordinates.matrix[vertex][coord];
      }
    }
  }
  return status;
}

int affine_rotate(data_t *data, double angles[3], int upd_min_max) {
  // function performs rotation of 3D model: angle_x, angle_y and angle_z
  // are angles of rotation (in radians) around x, y and z axes correspondingly.
  int status = OK;
  for (int coord = 0; coord < 3; coord++) {
    if (isnan(angles[coord]) || isinf(angles[coord])) {
      return ERROR;
    }
  }
  if (fabs(angles[0]) < 1e-6 && fabs(angles[1]) < 1e-6 &&
      fabs(angles[2]) < 1e-6) {
    return OK;
  }
  matrix_t M_rotation, r_vertex, r_result;
  s21_create_matrix(3, 3, &M_rotation);
  s21_create_matrix(3, 1, &r_vertex);
  M_rotation.matrix[0][0] = cos(angles[1]) * cos(angles[2]);
  M_rotation.matrix[0][1] = -sin(angles[2]) * cos(angles[1]);
  M_rotation.matrix[0][2] = sin(angles[1]);
  M_rotation.matrix[1][0] = sin(angles[0]) * sin(angles[1]) * cos(angles[2]) +
                            sin(angles[2]) * cos(angles[0]);
  M_rotation.matrix[1][1] = -sin(angles[0]) * sin(angles[1]) * sin(angles[2]) +
                            cos(angles[0]) * cos(angles[2]);
  M_rotation.matrix[1][2] = -sin(angles[0]) * cos(angles[1]);
  M_rotation.matrix[2][0] = sin(angles[0]) * sin(angles[2]) -
                            sin(angles[1]) * cos(angles[0]) * cos(angles[2]);
  M_rotation.matrix[2][1] = sin(angles[0]) * cos(angles[2]) +
                            sin(angles[1]) * cos(angles[0]) * sin(angles[2]);
  M_rotation.matrix[2][2] = cos(angles[0]) * cos(angles[1]);
  for (int vertex = 0; vertex < data->amount_of_vertexes; vertex++) {
    for (int coord = 0; coord < 3; coord++) {
      r_vertex.matrix[coord][0] = data->coordinates.matrix[vertex][coord];
    }
    status = s21_mult_matrix(&M_rotation, &r_vertex, &r_result);
    for (int coord = 0; coord < 3; coord++) {
      (data->coordinates.matrix[vertex][coord]) = r_result.matrix[coord][0];
    }
  }
  if (upd_min_max == 1) {
    get_min_max(data);
  }
  s21_remove_matrix(&M_rotation);
  s21_remove_matrix(&r_vertex);
  s21_remove_matrix(&r_result);
  return status;
}

int affine_scale(data_t *data, double scale) {
  int status = OK;
  if (fabs(scale) < 1e-6 || isnan(scale) || isinf(scale)) {  // epsilon???
    return ERROR;
  }
  for (int vertex = 0; vertex < data->amount_of_vertexes; vertex++) {
    for (int coord = 0; coord < 3; coord++) {
      data->coordinates.matrix[vertex][coord] *= scale;
    }
  }
  for (int i = 0; i < 6; i++) {
    data->min_max[i] *= scale;
  }
  return status;
}

int affine_translate(data_t *data, double r_translation[3]) {
  int status = OK;
  for (int coord = 0; coord < 3; coord++) {
    if (isnan(r_translation[coord]) || isinf(r_translation[coord])) {
      return ERROR;
    }
  }
  if (fabs(r_translation[0]) < 1e-6 && fabs(r_translation[1]) < 1e-6 &&
      fabs(r_translation[2]) < 1e-6) {
    return OK;
  }
  for (int vertex = 0; vertex < data->amount_of_vertexes; vertex++) {
    for (int coord = 0; coord < 3; coord++) {
      data->coordinates.matrix[vertex][coord] += r_translation[coord];
    }
  }
  for (int coord = 0; coord < 3; coord++) {
    data->min_max[coord * 2] += r_translation[coord];
    data->min_max[coord * 2 + 1] += r_translation[coord];
  }
  return status;
}

int normalize_model_data(data_t *data) {
  int status = OK;
  double r_center[3] = {0};
  double max = 0;
  // status = get_min_max(data);
  if (data == NULL || data->amount_of_vertexes <= 0 ||
      s21_check_matrix(&(data->coordinates)) != MATRIX_OP_OK) {
    return ERROR;
  }
  if (data->amount_of_vertexes != 1) {
    r_center[0] = -(data->min_max[1] + data->min_max[0]) / 2;
    r_center[1] = -(data->min_max[3] + data->min_max[2]) / 2;
    r_center[2] = -(data->min_max[5] + data->min_max[4]) / 2;
    status = affine_translate(data, r_center);
  }
  max = 1. / sqrt(pow(fmax(fabs(data->min_max[0]), fabs(data->min_max[1])), 2) +
                  pow(fmax(fabs(data->min_max[2]), fabs(data->min_max[3])), 2) +
                  pow(fmax(fabs(data->min_max[4]), fabs(data->min_max[5])), 2));
  if (status == OK && fabs(max) > 1e-6) {
    status = affine_scale(data, max);
  }
  return status;
}
