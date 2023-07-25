#ifndef MY_MATH_H_
#define MY_MATH_H_

#define INT_MAX 2147483647
#define MY_PI 3.14159265358979323846
#define MY_NAN 0.0 / 0.0
#define MY_INF_POS +1.0 / 0.0
#define MY_INF_NEG -1.0 / 0.0
#define MY_LN2 0.693147180559945309417232
#define MY_E 2.71828182845904523536028747

#define MY_IS_NAN(x) (x != x)
#define MY_IS_INF(x) (x == MY_INF_NEG || x == MY_INF_POS)

int my_abs(int x);
long double my_acos(double x);
long double my_asin(double x);
long double my_atan(double x);
long double my_ceil(double x);
long double my_cos(double x);
long double my_exp(double x);
long double my_fabs(double x);
long double my_floor(double x);
long double my_fmod(double x, double y);
long double my_log(double x);
long double my_pow(double base, double exp);
long double my_sin(double x);
long double my_sqrt(double x);
long double my_tan(double x);
long double my_factorial(long long int x);

#endif  //  MY_MATH_H_