#include "my_math.h"

int my_abs(int x) { return (int)my_fabs(x); }

long double my_ceil(double x) {
  long double result = (long long int)x;
  if (MY_IS_NAN(x) || MY_IS_INF(x)) {
    result = x;
  } else if ((x > -1.) && (x < 0.0)) {
    result = -0.0;
  } else if ((x > 0.) && (x != result)) {
    result += 1;
  }
  return result;
}

long double my_fabs(double x) {
  if (x < 0) {
    x = -x;
  }
  return (long double)x;
}

long double my_floor(double x) {
  long double result = (long long int)x;
  if ((x < 0.) && (x != result)) {
    result -= 1;
  }
  return result;
}

long double my_fmod(double x, double y) {
  int flag_minus_x = (x < 0 ? 1 : 0), flag_minus_y = (y < 0 ? 1 : 0);
  double buffer = y;
  x = my_fabs(x);
  y = my_fabs(y);
  if (y != 0) {
    while (y < x) {
      y += buffer;
    }
    y -= buffer;
    x = x - y;
  } else {
    x = MY_NAN;
  }
  x = (flag_minus_x == 1 ? -x : x);
  x = (flag_minus_y == 1 ? -x : x);
  return (long double)(x);
}

long double my_asin(double x) {
  long double result = 0;
  if (MY_IS_NAN(x) || MY_IS_INF(x)) {
    result = MY_NAN;
  } else {
    if (x == 1.0)
      result = MY_PI / 2;
    else if (x == -1.0)
      result = -MY_PI / 2;
    else
      result = my_atan((x) / my_sqrt(1 - my_pow(x, 2)));
  }
  return result;
}

long double my_acos(double x) {
  long double result = MY_PI / 2;
  if (MY_IS_NAN(x) || MY_IS_INF(x)) {
    result = MY_NAN;
  } else {
    if (my_fabs(x) > 1.0) {
      result = MY_NAN;
    } else if (x == 1.0) {
      result = 0;
    } else if (x == (-1.0)) {
      result = MY_PI;
    } else if (x > 0) {
      result = my_atan(my_sqrt(1 - my_pow(x, 2)) / (x));
    } else if (x < 0) {
      result = MY_PI + my_atan(my_sqrt(1 - my_pow(x, 2)) / (x));
    }
  }
  return result;
}

long double my_atan(double x) {
  long double result = 0;
  long double argument = x;

  if (my_fabs(x) > 1) {
    argument = 1 / x;
  }

  long double mono = argument;

  for (int i = 1; i < 10; i++) {
    result += mono;
    mono *= (-1) * argument * argument / (2 * i + 1) / (2 * i - 1);
  }

  if (my_fabs(x) > 1) {
    result = MY_PI / 2 - result;
  }

  return result;
}

long double my_cos(double x) {
  long double result = 1.0;
  int znak = -1;
  if (MY_IS_NAN(x) || MY_IS_INF(x)) {
    result = MY_NAN;
  } else {
    x = my_fmod(x, MY_PI * 2.0);

    if ((x > (MY_PI / 2.0)) && (x <= MY_PI)) {
      x = MY_PI - x;
    } else if (x > MY_PI && x <= ((MY_PI * 3.0) / 2.0)) {
      x -= MY_PI;
    } else if (x > ((MY_PI * 3.0) / 2.0) && x <= (MY_PI * 2.0)) {
      x = (2.0 * MY_PI) - x;
      znak = 1;
    } else {
      znak = 1;
    }

    long double valueTailor = 1.0;
    for (int i = 1; i < 200; i++) {
      result += (valueTailor =
                     ((-valueTailor) * x * x) / ((2.0 * i - 1) * (2.0 * i)));
    }
    result *= znak;
  }
  return result;
}

long double my_factorial(long long int x) {
  long double result = 1;
  result = ((x == 0) || (x == 1)) ? 1 : x * my_factorial(x - 1);
  return result;
}

long double my_exp(double x) {  // 1 + x + x^2 / 2! + x^3 / 3! + ...
  long double result = 0;
  if (x > 709) {
    result = MY_INF_POS;
  } else if ((x != MY_INF_NEG) && (x >= -20)) {
    result = 1 + x;
    long double mult_x = x;
    for (int i = 2; i < 97; i++) {
      mult_x *= x;
      result += mult_x / my_factorial(i);
    }
  }
  return result;
}

long double my_log(double x) {
  long double result = 0, compare = 0;
  int e_repeat = 0;
  if (x == MY_INF_POS) {
    result = x;
  } else if (x == 0) {
    result = MY_INF_NEG;
  } else if (x < 0) {
    result = MY_NAN;
  } else {
    for (; x >= MY_E; e_repeat++) {
      x /= MY_E;
    }
    for (int i = 0; i < 100; i++) {
      compare = result;
      result = compare + 2 * (x - my_exp(compare)) / (x + my_exp(compare));
    }
    result += e_repeat;
  }
  return result;
}

long double my_pow(double x, double y) {
  long double result = 0;
  if ((y == 0.0) || (x == 1.0) || (MY_IS_INF(y) && (my_fabs(x) == 1.0))) {
    result = 1.;
  } else if (((MY_IS_NAN(x)) && (MY_IS_NAN(y))) ||
             ((x < 0) && (my_fabs(y) < 1))) {
    result = MY_NAN;
  } else if (((x == 0.0) && (y < 0.0)) ||
             (MY_IS_INF(y) && (my_fabs(x) > 1.0) && (y > 0.0)) ||
             (MY_IS_INF(y) && (my_fabs(x) < 1.0) && (y < 0.0))) {
    result = MY_INF_POS;
  } else if ((x == 0.0) ||
             (MY_IS_INF(y) && (my_fabs(x) > 1.0) && (y < 0.0)) ||
             (MY_IS_INF(y) && (my_fabs(x) < 1.0) && (y > 0.0))) {
    result = 0.0;
  } else {
    result = my_exp(y * my_log(my_fabs(x)));
    if (x < 0.0 && my_fmod(y, 2.0) != 0.0) {
      result *= -1;
    }
  }
  return result;
}

long double my_sin(double x) {
  long double result = x;
  int znak = -1;
  if (MY_IS_NAN(x) || MY_IS_INF(x)) {
    result = MY_NAN;
  } else {
    x = my_fmod(x, MY_PI * 2.0);

    if ((x > (MY_PI / 2.0)) && (x <= MY_PI)) {
      x = MY_PI - x;
      znak = 1;
    } else if (x > MY_PI && x <= ((MY_PI * 3.0) / 2.0))
      x -= MY_PI;
    else if (x > ((MY_PI * 3.0) / 2.0) && x <= (MY_PI * 2.0))
      x = (2.0 * MY_PI) - x;
    else
      znak = 1;

    result = (long double)x;
    long double valueTailor = (long double)x;
    for (int i = 1; my_fabs(valueTailor / result) > 1e-100; i += 1) {
      result += (valueTailor =
                     ((-valueTailor) * x * x) / ((2.0 * i + 1) * (2.0 * i)));
    }
    result *= znak;
  }
  return result;
}

long double my_sqrt(double x) { return my_pow(x, 0.5); }

long double my_tan(double x) {
  long double result = 0.0;
  if (MY_IS_NAN(x) || MY_IS_INF(x)) {
    result = MY_NAN;
  } else {
    result = my_sin(x) / my_cos(x);
  }
  return result;
}
