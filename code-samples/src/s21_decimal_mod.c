#include <stdio.h>

#include "s21_decimal.h"
#include "supp_func.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  int sign = get_sign(value_1.bits[3]);
  int exp1 = get_exp(value_1.bits[3]), exp2 = get_exp(value_2.bits[3]);
  memset(result, 0, 16);
  int flag_less = 0;
  if (!s21_is_less(abs_decimal(value_1), abs_decimal(value_2))) {
    value_1.bits[3] = 0;
    value_2.bits[3] = 0;
    int overflow_flag = 0;
    s21_big_decimal bv1 = convert_dec_to_big(value_1),
                    bv2 = convert_dec_to_big(value_2);
    if (exp1 < exp2) {
      while (exp1 < exp2) {
        _x10(&bv1);
        ++exp1;
        if (bv1.bits[3] > 0) overflow_flag = 1;
      }

    } else if (exp1 > exp2) {
      while (exp1 > exp2) {
        _x10(&bv2);
        ++exp2;
        if (bv2.bits[3] > 0) overflow_flag = 1;
      }
    }
    if (!is_dec_zero(value_2)) {
      s21_big_decimal temp = {0};
      temp = s21_div_supp(bv1, bv2, &bv1);
      for (int i = 0; i < 3; ++i) result->bits[i] = temp.bits[i];
      if (overflow_flag) s21_truncate(*result, result);
    } else {
      err = 3;
    }
  } else if (!is_dec_zero(value_2)) {
    *result = value_1;
    flag_less = 1;
  } else {
    err = 3;
  }
  if (!flag_less) set_exp(exp2, &(result->bits[3]));
  if (sign && !flag_less) s21_negate(*result, result);
  return err;
}
