#include <time.h>

#include "s21_viewer.h"

void s21_init_data(data_t *data) {
  data->amount_of_facets = 0;
  data->amount_of_vertexes = 0;
  for (int n = 0; n < 6; n++) {
    data->min_max[n] = 0;
  }
  data->coordinates.matrix = NULL;
  data->coordinates.rows = 0;
  data->coordinates.columns = 0;
  data->polygons = NULL;
}

void s21_remove_polygon(polygon_t **polygon, int amount_of_facets) {
  if ((*polygon) != NULL) {
    for (int i = 0; i < amount_of_facets; i++) {
      if ((*polygon)[i].vertexes != NULL) {
        free((*polygon)[i].vertexes);
        (*polygon)[i].vertexes = NULL;
        (*polygon)[i].numbers_of_vertexes_in_facets = 0;
      }
    }
    free(*polygon);
    (*polygon) = NULL;
  }
}

/// @brief чистит память
/// @param data
void s21_remove_data(data_t *data) {
  s21_remove_matrix(&(data->coordinates));
  s21_remove_polygon(&(data->polygons), data->amount_of_facets);
  data->amount_of_facets = 0;
  data->amount_of_vertexes = 0;
  for (int n = 0; n < 6; n++) {
    data->min_max[n] = 0;
  }
}

/// @brief увеличиваем размер матрицы
/// @param A матрица
int s21_increasing_matrix(matrix_t *A) {
  double **temp_matrix;
  double *temp_row;
  int status = OK;
  A->rows++;
  temp_matrix = (double **)realloc(A->matrix, (sizeof(double *) * (A->rows)));
  if (temp_matrix != NULL) {
    A->matrix = temp_matrix;
    temp_row = (double *)calloc(3, sizeof(double));
    if (temp_row != NULL) {
      A->matrix[A->rows - 1] = temp_row;
    } else {
      status = ERROR_MEMORY;
    }
  } else {
    status = ERROR_MEMORY;
  }
  return status;
}

/// @brief добавляем значения x,y,z
/// @param A  матрица с координатами
/// @param str строка с координатами вершины
int s21_set_data(matrix_t *A, char *str, double *min_max) {
  double value = 0.0;
  int status = OK;
  if (A && A->rows == 0 && A->columns == 0) {
    status = s21_create_matrix(1, 3, A);
  } else {
    status = s21_increasing_matrix(A);
  }
  if (status == OK) {
    str += 2;
    char *istr = strtok(str, " ");
    for (int i = 0; i < 3; i++) {
      value = atof(istr);
      A->matrix[A->rows - 1][i] = value;
      if (min_max[2 * i] > value) {
        min_max[2 * i] = value;
      } else if (min_max[2 * i + 1] < value) {
        min_max[2 * i + 1] = value;
      }
      istr = strtok(NULL, " ");
    }
  }
  return status;
}

/// @brief добавляем значения поверхностей
/// @param str строка с точками
/// @param polygon структура с определениями поверхностей
/// @param amount количество f
/// @return значение ошибок
int s21_facets_data(char *str, polygon_t **polygon, int amount) {
  int status = OK, n_vertices = 0;
  polygon_t *tmp_polygon_pointer = NULL;
  int *tmp_vertices_ptr = NULL;

  if (amount == 0) {
    tmp_polygon_pointer = (polygon_t *)calloc(1, sizeof(polygon_t));
  } else {
    tmp_polygon_pointer =
        (polygon_t *)realloc((*polygon), (sizeof(polygon_t) * (amount + 1)));
  }
  if (tmp_polygon_pointer == NULL) {
    status = ERROR_MEMORY;
  } else {
    *polygon = tmp_polygon_pointer;
    (*polygon)[amount].numbers_of_vertexes_in_facets = 0;
    (*polygon)[amount].vertexes = NULL;
  }
  str += 2;
  char *istr = strtok(str, " ");
  while (status == OK && istr != NULL && atoi(istr) > 0) {
    if (n_vertices == 0) {
      tmp_vertices_ptr = (int *)calloc(1, sizeof(int));
    } else {
      tmp_vertices_ptr = (int *)realloc((*polygon)[amount].vertexes,
                                        sizeof(int) * (n_vertices + 1));
    }
    if (tmp_vertices_ptr == NULL) {
      status = ERROR_MEMORY;
    } else {
      (*polygon)[amount].vertexes = tmp_vertices_ptr;
    }
    (*polygon)[amount].vertexes[n_vertices] = atoi(istr);
    istr = strtok(NULL, " ");
    n_vertices++;
  }
  if (status == OK) {
    (*polygon)[amount].numbers_of_vertexes_in_facets = n_vertices;
  }
  return status;
}

/// @brief читаем и проверяем .obj файл
/// @param file название файла ///нужно ли проверять, что файл .obj?????
/// @param data
/// @return значение ошибки
int s21_parser(const char *file, data_t *data) {
  int status = OK, cflags = REG_EXTENDED;
  FILE *fp = NULL;
  char *line = NULL;
  size_t len = 0;
  int comp_v = 0, comp_f = 0;
  regex_t re_v = {0}, re_f = {0};
  char v_rattern[] =
      "^[v]([ ]+[+-]?[0-9]+[.]?[0-9]*){3}((([ ]+[0-9]+[.]?[0-9]*)?)|([ "
      "]+[0-9]+[.]?[0-9]*([ "
      "]+([0]|[1]|(0.[0-9]*))){3}))[\n]?$";
  char f_pattern[] =
      "^[f]([ "
      "][1-9][0-9]*([/]([+-]?[0-9]+[.]?[0-9]*)?([/"
      "][+-]?[0-9]+[.]?[0-9]*)?)?){3,}[ ]?[\n]?$";
  fp = fopen(file, "r");
  comp_v = regcomp(&re_v, v_rattern, cflags);
  comp_f = regcomp(&re_f, f_pattern, cflags);
  if (fp == NULL) {
    status = ERROR_FILE;
  } else if (comp_v != 0 || comp_f != 0) {
    status = ERROR;
  } else if (data == NULL) {
    status = ERROR_DATA;
  } else {
    while ((status == OK) && (getline(&line, &len, fp) != -1)) {
      if (line[0] == 'v' && line[1] == ' ') {
        if (regexec(&re_v, line, 0, NULL, 0) == 0) {
          status = s21_set_data(&data->coordinates, line, data->min_max);
        }
      } else if (line[0] == 'f') {
        if (regexec(&re_f, line, 0, NULL, 0) == 0) {
          status =
              s21_facets_data(line, &(data->polygons), data->amount_of_facets);
          data->amount_of_facets++;
        }
      }
    }
    if (line) {
      free(line);
    }
    fclose(fp);
    data->amount_of_vertexes = data->coordinates.rows;
  }
  regfree(&re_v);
  regfree(&re_f);
  return status;
}
