#include <stdio.h>

#include "s21_decimal.h"
#include "supp_func.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int res = 0;
  if (result == NULL) {
    res = 1;
  } else {
    for (int i = 0; i <= 3; i++) result->bits[i] = value.bits[i];
    if (get_sign(value.bits[3]))
      set_bit(&(result->bits[3]), 31, 0);
    else
      set_bit(&(result->bits[3]), 31, 1);
  }
  return res;
}

int s21_negate_big(s21_big_decimal value, s21_big_decimal *result) {
  int res = 0;
  for (int i = 0; i <= 6; i++) result->bits[i] = value.bits[i];
  if (get_sign(value.bits[6]))
    set_bit(&(result->bits[6]), 31, 0);
  else
    set_bit(&(result->bits[6]), 31, 1);
  return res;
}

int floor_round_trunc(s21_decimal value, s21_decimal *result, char mode) {
  int err = 0;
  if (result == NULL) {
    err = 1;
  } else {
    int exp = get_exp(value.bits[3]);
    if (exp > 0) {
      s21_big_decimal rest;
      int sign = get_sign(value.bits[3]);
      if (sign) s21_negate(value, &value);
      s21_big_decimal temp = convert_dec_to_big(value);
      while (exp != 0) {
        rest = div10(&temp);
        --exp;
      }
      if (mode == 'f') {
        if (sign) {
          plus_one_big(&temp);
          convert_big_to_dec(temp, result, 0, 0);
          s21_negate(*result, result);
        } else {
          convert_big_to_dec(temp, result, 0, 0);
        }
      } else if (mode == 'r') {
        if (rest.bits[0] > 4) plus_one_big(&temp);
        convert_big_to_dec(temp, result, 0, 0);
        if (sign) s21_negate(*result, result);
      } else if (mode == 't') {
        convert_big_to_dec(temp, result, 0, 0);
        if (sign) s21_negate(*result, result);
      }
    }
  }
  return err;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int err = 0;
  if (result == NULL) {
    err = 1;
  } else {
    err = floor_round_trunc(value, result, 'f');
  }
  return err;
}
int s21_round(s21_decimal value, s21_decimal *result) {
  int err = 0;
  if (result == NULL) {
    err = 1;
  } else {
    err = floor_round_trunc(value, result, 'r');
  }
  return err;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int err = 0;
  if (result == NULL) {
    err = 1;
  } else {
    err = floor_round_trunc(value, result, 't');
  }
  return err;
}
