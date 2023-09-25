#include <stdio.h>

#include "s21_decimal.h"
#include "supp_func.h"
// 0 - FALSE   1 - TRUE
int s21_is_less(s21_decimal lhs, s21_decimal rhs) {
  int result = 1;
  if (get_sign(lhs.bits[3]) && !get_sign(rhs.bits[3])) {
    result = 1;

  } else if (!get_sign(lhs.bits[3]) && get_sign(rhs.bits[3])) {
    result = 0;
  } else if (s21_is_equal(lhs, rhs)) {
    result = 0;

  } else if (get_sign(lhs.bits[3]) && get_sign(rhs.bits[3])) {
    result = s21_is_less(abs_decimal(rhs), abs_decimal(lhs));
  } else {
    s21_big_decimal blhs = convert_dec_to_big(lhs),
                    brhs = convert_dec_to_big(rhs);
    make_equal_exp(&blhs, &brhs);
    result = s21_is_less_or_equal_big(blhs, brhs);
  }
  return result;
}

// тут нет проверки на знак, вызывается только для двух положительных
int s21_is_less_or_equal_big(s21_big_decimal lhs, s21_big_decimal rhs) {
  int result = 1;
  make_equal_exp(&lhs, &rhs);
  int break_flag = 0, ind = 5;
  while (ind >= 0 && !break_flag) {
    if (lhs.bits[ind] > rhs.bits[ind]) {
      result = 0;
      break_flag = 1;
    } else if (lhs.bits[ind] < rhs.bits[ind]) {
      result = 1;
      break_flag = 1;
    }
    --ind;
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal lhs, s21_decimal rhs) {
  int err = 0;
  if (s21_is_equal(lhs, rhs) || s21_is_less(lhs, rhs)) err = 1;
  return err;
}

int s21_is_greater(s21_decimal lhs, s21_decimal rhs) {
  int err = 0;
  if (!s21_is_equal(lhs, rhs) && !s21_is_less(lhs, rhs)) err = 1;
  return err;
}

int s21_is_greater_or_equal(s21_decimal lhs, s21_decimal rhs) {
  int err = 0;
  if (s21_is_equal(lhs, rhs) || !s21_is_less(lhs, rhs)) err = 1;
  return err;
}

int s21_is_equal(s21_decimal lhs, s21_decimal rhs) {
  int err = 1;
  s21_big_decimal bl = convert_dec_to_big(lhs);
  s21_big_decimal br = convert_dec_to_big(rhs);
  make_equal_exp(&bl, &br);
  for (int i = 0; i < 3; ++i) {
    if (bl.bits[i] != br.bits[i]) err = 0;
  }
  if (bl.bits[6] != br.bits[6]) err = 0;
  return err;
}

int s21_is_not_equal(s21_decimal lhs, s21_decimal rhs) {
  int err = 0;
  for (int i = 0; i < 4; ++i) {
    if (lhs.bits[i] != rhs.bits[i]) err = 1;
  }
  return err;
}
