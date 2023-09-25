#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "supp_func.h"

START_TEST(s21_mod_1) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;

  dec1.bits[0] = 10;
  dec2.bits[0] = 4;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 2;

  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_mod_2) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;

  dec1.bits[0] = 4036421147;
  dec1.bits[1] = 382;
  dec1.bits[2] = 262144;
  dec2.bits[0] = 2945631615;
  dec2.bits[1] = 658;
  dec2.bits[2] = 2147876864;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 867247046;
  true_ans.bits[1] = 90;
  true_ans.bits[2] = 393216;

  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(0, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_mod_4) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;

  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;

  dec2.bits[0] = 1;
  s21_decimal true_ans = {0};
  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_mod_5) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;

  dec1.bits[0] = 4294967295;
  dec1.bits[1] = 4294967295;
  dec1.bits[2] = 4294967295;
  dec2.bits[0] = 0;
  set_exp(5, &(dec1.bits[3]));
  set_exp(2, &(dec2.bits[3]));

  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(s21_mod_6) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;

  dec1.bits[0] = 5;
  dec2.bits[0] = 10;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 5;

  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}

START_TEST(s21_mod_7) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;

  dec1.bits[0] = 5;
  s21_negate(dec1, &dec1);
  dec2.bits[0] = 10;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 5;
  s21_negate(true_ans, &true_ans);

  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}

START_TEST(s21_mod_8) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;

  dec1.bits[0] = 10;
  dec2.bits[0] = 10;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 0;

  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}

START_TEST(s21_mod_9) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;

  dec1.bits[0] = 0;
  dec2.bits[0] = 10;

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 0;

  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(1, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}

START_TEST(s21_mod_10) {
  s21_decimal dec1 = {0};
  s21_decimal dec2 = {0};
  s21_decimal ans;

  dec1.bits[0] = 100;
  dec2.bits[0] = 100;

  set_exp(5, &(dec1.bits[3]));
  set_exp(2, &(dec2.bits[3]));

  s21_decimal true_ans = {0};
  true_ans.bits[0] = 0;

  int res = s21_mod(dec1, dec2, &ans);
  ck_assert_int_eq(0, s21_is_equal(ans, true_ans));
  ck_assert_int_eq(res, 0);
}

Suite *dec_mod_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_dec_mod");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_mod_1);
  tcase_add_test(tc_core, s21_mod_2);
  tcase_add_test(tc_core, s21_mod_4);
  tcase_add_test(tc_core, s21_mod_5);
  tcase_add_test(tc_core, s21_mod_6);
  tcase_add_test(tc_core, s21_mod_7);
  tcase_add_test(tc_core, s21_mod_8);
  tcase_add_test(tc_core, s21_mod_9);
  tcase_add_test(tc_core, s21_mod_10);
  suite_add_tcase(s, tc_core);
  return s;
}