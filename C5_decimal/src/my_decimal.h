#ifndef SRC_MY_DECIMAL_H_
#define SRC_MY_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIGN 0x80000000

enum returns { OK, INF, NEGATIVE_INF, DIVISION_BY_ZERO };

enum converts { SUCCESS, CONVERTING_ERROR };

enum boolian { FALSE, TRUE };

typedef struct {
  unsigned int bits[4];
} my_decimal;

typedef union {
  int ui;
  float fl;
} floatbits;

int my_add(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_sub(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_mul(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_div(my_decimal value_1, my_decimal value_2, my_decimal *result);
int my_mod(my_decimal value_1, my_decimal value_2, my_decimal *result);

int my_is_less(my_decimal value_1, my_decimal value_2);
int my_is_less_or_equal(my_decimal value_1, my_decimal value_2);
int my_is_greater(my_decimal value_1, my_decimal value_2);
int my_is_greater_or_equal(my_decimal value_1, my_decimal value_2);
int my_is_equal(my_decimal value_1, my_decimal value_2);
int my_is_not_equal(my_decimal value_1, my_decimal value_2);

int my_from_int_to_decimal(int src, my_decimal *dst);
int my_from_float_to_decimal(float src, my_decimal *dst);
int my_from_decimal_to_int(my_decimal src, int *dst);
int my_from_decimal_to_float(my_decimal src, float *dst);

int my_floor(my_decimal value, my_decimal *result);
int my_round(my_decimal value, my_decimal *result);
int my_truncate(my_decimal value, my_decimal *result);
int my_negate(my_decimal value, my_decimal *result);

int get_bit(const my_decimal decVar, int bit);
int get_sign(const my_decimal *varPtr);
int get_scale(const my_decimal *varPtr);
void scale_equalize(my_decimal *number_1, my_decimal *number_2);
void bits_copy(my_decimal src, my_decimal *dest);
void convert_to_addcode(my_decimal *number_1);
void set_scale(my_decimal *varPtr, int scale);
int offset_left(my_decimal *varPtr, int value_offset);
void init_struct(my_decimal *varPtr);
void set_bit(my_decimal *varPtr, int bit, int value);
void set_sign(my_decimal *varPtr, int sign);
void clean(my_decimal *varPtr);
int bit_addition(my_decimal var1, my_decimal var2, my_decimal *result);
void div_only_bits(my_decimal a, my_decimal b, my_decimal *buf,
                   my_decimal *result);
void sub_only_bits(my_decimal number_1, my_decimal number_2,
                   my_decimal *result);
int float_binary_exp(float *src);
int get_float_sign(float *src);
void minus_scale(my_decimal *a);
void swap_values(my_decimal *value1, my_decimal *value2);
int add_without_scale(my_decimal value_1, my_decimal value_2,
                      my_decimal *result);
int sub_without_scale(my_decimal value1, my_decimal value2, my_decimal *result);
int get_highest_bit(my_decimal dec);
int shift_left(my_decimal *dec, int shift);
my_decimal binary_division(my_decimal dec1, my_decimal dec2,
                           my_decimal *remainder, int *fail);
int sign_minus(my_decimal a);
int equalize_to_lower(my_decimal *dec, int scale);
int equalize_to_bigger(my_decimal *dec, int scale);
int equalize_scales(my_decimal *dec1, my_decimal *dec2, int scale);
int processing_eq_scales(my_decimal *value_1, my_decimal *value_2,
                         int *final_scale);

#endif  // SRC_MY_DECIMAL_H_
