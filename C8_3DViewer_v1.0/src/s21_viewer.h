#ifndef S21_VIEWER_H
#define S21_VIEWER_H

#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "s21_matrix/s21_matrix.h"

typedef enum {
  OK = 0,
  ERROR = 1,
  ERROR_FILE,
  ERROR_MEMORY,
  ERROR_DATA,
} VIEWER_STATUS;

typedef struct facets {
  int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data {
  int amount_of_vertexes;
  int amount_of_facets;
  double min_max[6];  // min_x, max_x, min_y, max_y, min_z, max_z
  matrix_t coordinates;
  polygon_t *polygons;
} data_t;

// affine transformations

int get_min_max(data_t *data);
int affine_translate(data_t *data, double r_translation[3]);
int affine_rotate(data_t *data, double angles[3], int upd_min_max);
int affine_scale(data_t *data, double scale);
int normalize_model_data(data_t *data);

// parser
void s21_init_data(data_t *data);
int s21_parser(const char *file, data_t *data);
int s21_facets_data(char *str, polygon_t **polygon, int amount);
int s21_set_data(matrix_t *A, char *str, double *min_max);
int s21_increasing_matrix(matrix_t *A);
void s21_remove_polygon(polygon_t **polygon, int amount_of_facets);
void s21_remove_data(data_t *data);

#endif  // S21_VIEWER_H
