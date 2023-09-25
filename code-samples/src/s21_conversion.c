#include "s21_decimal.h"
#include "supp_func.h"
// #include <math.h>
#include <stdlib.h>

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int err = 0;
  if (dst == NULL) return 1;
  memset(dst, 0, 16);
  union {
    float f;
    int i;
  } u;
  u.f = fabs(src);
  if (src < 0) set_bit(&(dst->bits[3]), 31, 1);
  int exp = (u.i >> 23) - 127;

  int mant = u.i << 9;
  mant >>= 9;
  s21_big_decimal val = {0};
  val.bits[0] = 0b00010000000000000000000000000000;
  val.bits[1] = 0b00111110001001010000001001100001;
  val.bits[2] = 0b00100000010011111100111001011110;
  if (exp >= 0) {
    while (exp) {
      shuffle_big_dec_left(&val);
      --exp;
    }
  } else {
    while (exp != 0) {
      shuffle_big_dec_right(&val);
      ++exp;
      if (is_big_dec_zero(val) && exp < 0) err = 1;
    }
  }
  if (!err) {
    s21_big_decimal temp = val;
    int indicator = 1 << 22;
    while (indicator) {
      shuffle_big_dec_right(&temp);
      if (indicator & mant) sum_equal_exp(val, temp, &val, 191);
      indicator >>= 1;
    }
    make_7_digits(&val);
    for (int i = 0; i < 3; ++i) {
      dst->bits[i] = val.bits[i];
    }
    dst->bits[3] = val.bits[6];
    if (src < 0) s21_negate(*dst, dst);
  }
  return err;
}

void make_7_digits(s21_big_decimal *val) {
  s21_big_decimal temp = {0};
  int exp = 28;
  while (val->bits[0] >= 10000000 || val->bits[1] != 0 || val->bits[2] != 0 ||
         val->bits[3] != 0 || val->bits[4] != 0 || val->bits[5] != 0 ||
         exp > 7) {
    temp = div10(val);
    --exp;
  }
  if (temp.bits[0] >= 5) {
    temp.bits[0] = 1;
    sum_equal_exp(*val, temp, val, 191);
  }
  while (exp < 0) {
    _x10(val);
    ++exp;
  }
  temp = div10(val);
  --exp;
  while (is_big_dec_zero(temp) && exp > 0) {
    temp = div10(val);
    --exp;
  }
  _x10(val);
  sum_equal_exp(*val, temp, val, 191);
  ++exp;
  set_exp(exp, &(val->bits[6]));
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err = 0;
  if (dst == NULL) {
    err = 1;
  } else {
    *dst = 0.0;
    double temp = 1.0, result = 0.0;
    int sign = get_sign(src.bits[3]);
    int exp = get_exp((src.bits[3]));
    s21_big_decimal b_src = convert_dec_to_big(src);
    src.bits[3] = 0;
    while (!is_big_dec_zero(b_src)) {
      (b_src.bits[0] & 1) ? result += temp : 1;
      temp *= 2;
      shuffle_big_dec_right(&b_src);
    }
    while (exp) {
      result /= 10;
      --exp;
    }
    if (result > MAX_FLT)
      err = 1;
    else {
      *dst = result;
      if (sign) *dst *= -1;
    }
  }
  return err;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;
  memset(dst, 0, 16);
  if (src < 0) {
    dst->bits[0] = 0 - src;
    s21_negate(*dst, dst);
  } else {
    dst->bits[0] = src;
  }

  return result;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int err = 0;
  int exp = get_exp(src.bits[3]);
  int sign = get_sign(src.bits[3]) ? -1 : 1;
  if (exp == 0) {
    if (src.bits[1] == 0 && src.bits[2] == 0 &&
        (src.bits[0] <= MAX_INT || sign == -1)) {
      *dst = src.bits[0] * sign;
    } else
      err = 1;
  } else {
    s21_big_decimal temp = convert_dec_to_big(src);
    while (exp > 0) {
      div10(&temp);
      --exp;
    }
    if (is_big_dec_zero(temp)) {
      *dst = 0;
    } else {
      set_exp(exp, &(temp.bits[6]));
      convert_big_to_dec(temp, &src, exp, 0);
      err = s21_from_decimal_to_int(src, dst);
    }
  }
  return err;
}
