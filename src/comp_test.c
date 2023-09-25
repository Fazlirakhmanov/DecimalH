#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "supp_func.h"

START_TEST(s21_equal_1) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  dec2.bits[0] = 100;
  ck_assert_int_eq(1, s21_is_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_equal_2) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 101;
  dec2.bits[0] = 100;
  ck_assert_int_eq(0, s21_is_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_equal_3) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  s21_negate(dec1, &dec1);
  dec2.bits[0] = 100;
  ck_assert_int_eq(0, s21_is_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_equal_4) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 1;
  set_exp(2, &dec2.bits[3]);
  dec2.bits[0] = 100;
  ck_assert_int_eq(1, s21_is_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_equal_5) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 1;
  set_exp(2, &dec2.bits[3]);
  dec2.bits[0] = 101;
  ck_assert_int_eq(0, s21_is_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_less_or_equal_1) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  dec2.bits[0] = 100;
  ck_assert_int_eq(1, s21_is_less_or_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_less_or_equal_2) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 101;
  dec2.bits[0] = 100;
  ck_assert_int_eq(0, s21_is_less_or_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_less_or_equal_3) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  s21_negate(dec1, &dec1);
  dec2.bits[0] = 0;
  ck_assert_int_eq(1, s21_is_less_or_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_less_or_equal_4) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 1;
  set_exp(2, &dec2.bits[3]);
  dec2.bits[0] = 100;
  ck_assert_int_eq(1, s21_is_less_or_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_less_or_equal_5) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 1;
  set_exp(2, &dec2.bits[3]);
  dec2.bits[0] = 101;
  ck_assert_int_eq(1, s21_is_less_or_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_less_or_equal_6) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  s21_negate(dec1, &dec1);
  s21_negate(dec2, &dec2);
  dec2.bits[0] = 10;
  ck_assert_int_eq(1, s21_is_less_or_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_less_1) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  dec2.bits[0] = 100;
  ck_assert_int_eq(0, s21_is_less(dec1, dec2));
}
END_TEST

START_TEST(s21_less_2) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 101;
  dec2.bits[0] = 100;
  ck_assert_int_eq(0, s21_is_less(dec1, dec2));
}
END_TEST

START_TEST(s21_less_3) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  s21_negate(dec1, &dec1);
  dec2.bits[0] = 0;
  ck_assert_int_eq(1, s21_is_less(dec1, dec2));
}
END_TEST

START_TEST(s21_less_4) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 1;
  set_exp(2, &dec2.bits[3]);
  dec2.bits[0] = 100;
  ck_assert_int_eq(0, s21_is_less(dec1, dec2));
}
END_TEST

START_TEST(s21_less_5) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 1;
  set_exp(2, &dec2.bits[3]);
  dec2.bits[0] = 101;
  ck_assert_int_eq(1, s21_is_less(dec1, dec2));
}
END_TEST

START_TEST(s21_less_6) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  s21_negate(dec1, &dec1);
  s21_negate(dec2, &dec2);
  dec2.bits[0] = 10;
  ck_assert_int_eq(1, s21_is_less(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_1) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  dec2.bits[0] = 100;
  ck_assert_int_eq(0, s21_is_greater(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_2) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 101;
  dec2.bits[0] = 100;
  ck_assert_int_eq(1, s21_is_greater(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_3) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  s21_negate(dec1, &dec1);
  dec2.bits[0] = 0;
  ck_assert_int_eq(0, s21_is_greater(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_4) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 1;
  set_exp(2, &dec2.bits[3]);
  dec2.bits[0] = 100;
  ck_assert_int_eq(0, s21_is_greater(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_5) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 1;
  set_exp(2, &dec2.bits[3]);
  dec2.bits[0] = 101;
  ck_assert_int_eq(0, s21_is_greater(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_6) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  s21_negate(dec1, &dec1);
  s21_negate(dec2, &dec2);
  dec2.bits[0] = 10;
  ck_assert_int_eq(0, s21_is_greater(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_or_equal_1) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  dec2.bits[0] = 100;
  ck_assert_int_eq(1, s21_is_greater_or_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_or_equal_2) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 101;
  dec2.bits[0] = 100;
  ck_assert_int_eq(1, s21_is_greater_or_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_or_equal_3) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  s21_negate(dec1, &dec1);
  dec2.bits[0] = 0;
  ck_assert_int_eq(0, s21_is_greater_or_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_or_equal_4) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 1;
  set_exp(2, &dec2.bits[3]);
  dec2.bits[0] = 100;
  ck_assert_int_eq(1, s21_is_greater_or_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_or_equal_5) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 1;
  set_exp(2, &dec2.bits[3]);
  dec2.bits[0] = 101;
  ck_assert_int_eq(0, s21_is_greater_or_equal(dec1, dec2));
}
END_TEST

START_TEST(s21_greater_or_equal_6) {
  s21_decimal dec1 = {0}, dec2 = {0};
  dec1.bits[0] = 100;
  s21_negate(dec1, &dec1);
  s21_negate(dec2, &dec2);
  dec2.bits[0] = 10;
  ck_assert_int_eq(0, s21_is_greater_or_equal(dec1, dec2));
}
END_TEST

START_TEST(test_is_equal_1) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  int res = s21_is_equal(a, b);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_equal_5) {
  s21_decimal a = {{0, 52, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  int res = s21_is_equal(a, b);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_equal_6) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{1747, 0, 1, 0}};
  int res = s21_is_equal(a, b);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_equal_10) {
  s21_decimal a = {0};
  s21_decimal b = {0};
  int res = s21_is_equal(a, b);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal_1) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 2, 0}};
  int res = s21_is_greater_or_equal(a, b);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_greater_or_equal_2) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 2, 0}};
  int res = s21_is_greater_or_equal(b, a);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_greater_or_equal_3) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  int res = s21_is_greater_or_equal(b, a);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_greater_1) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 2, 0}};
  int res = s21_is_greater(a, b);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_greater_2) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 2, 0}};
  int res = s21_is_greater(b, a);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_greater_3) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  int res = s21_is_greater(b, a);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_less_or_equal_1) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 2, 0}};
  int res = s21_is_less_or_equal(a, b);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_2) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 2, 0}};
  int res = s21_is_less_or_equal(b, a);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_less_or_equal_3) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  int res = s21_is_less_or_equal(b, a);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_less_1) {
  s21_decimal a = {{4294967295, 0, 0, 0}};
  s21_decimal b = {{0, 1, 0, 0}};
  int res = s21_is_less(a, b);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_is_less_2) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 2, 0}};
  int res = s21_is_less(b, a);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_less_3) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  int res = s21_is_less(b, a);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_not_equal_1) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  int res = s21_is_not_equal(a, b);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_is_not_equal_5) {
  s21_decimal a = {{0, 52, 1, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  int res = s21_is_not_equal(a, b);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *dec_comp_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_dec_comp");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_equal_1);
  tcase_add_test(tc_core, s21_equal_2);
  tcase_add_test(tc_core, s21_equal_3);
  tcase_add_test(tc_core, s21_equal_4);
  tcase_add_test(tc_core, s21_equal_5);
  tcase_add_test(tc_core, s21_less_or_equal_1);
  tcase_add_test(tc_core, s21_less_or_equal_2);
  tcase_add_test(tc_core, s21_less_or_equal_3);
  tcase_add_test(tc_core, s21_less_or_equal_4);
  tcase_add_test(tc_core, s21_less_or_equal_5);
  tcase_add_test(tc_core, s21_less_or_equal_6);
  tcase_add_test(tc_core, s21_less_1);
  tcase_add_test(tc_core, s21_less_2);
  tcase_add_test(tc_core, s21_less_3);
  tcase_add_test(tc_core, s21_less_4);
  tcase_add_test(tc_core, s21_less_5);
  tcase_add_test(tc_core, s21_less_6);
  tcase_add_test(tc_core, s21_greater_1);
  tcase_add_test(tc_core, s21_greater_2);
  tcase_add_test(tc_core, s21_greater_3);
  tcase_add_test(tc_core, s21_greater_4);
  tcase_add_test(tc_core, s21_greater_5);
  tcase_add_test(tc_core, s21_greater_6);
  tcase_add_test(tc_core, s21_greater_or_equal_1);
  tcase_add_test(tc_core, s21_greater_or_equal_2);
  tcase_add_test(tc_core, s21_greater_or_equal_3);
  tcase_add_test(tc_core, s21_greater_or_equal_4);
  tcase_add_test(tc_core, s21_greater_or_equal_5);
  tcase_add_test(tc_core, s21_greater_or_equal_6);
  tcase_add_test(tc_core, test_is_equal_1);
  tcase_add_test(tc_core, test_is_equal_5);
  tcase_add_test(tc_core, test_is_equal_6);
  tcase_add_test(tc_core, test_is_equal_10);
  tcase_add_test(tc_core, test_is_greater_or_equal_1);
  tcase_add_test(tc_core, test_is_greater_or_equal_2);
  tcase_add_test(tc_core, test_is_greater_or_equal_3);
  tcase_add_test(tc_core, test_is_equal_1);
  tcase_add_test(tc_core, test_is_equal_5);
  tcase_add_test(tc_core, test_is_equal_6);
  tcase_add_test(tc_core, test_is_equal_10);
  tcase_add_test(tc_core, test_is_greater_or_equal_1);
  tcase_add_test(tc_core, test_is_greater_or_equal_2);
  tcase_add_test(tc_core, test_is_greater_or_equal_3);
  tcase_add_test(tc_core, test_is_greater_1);
  tcase_add_test(tc_core, test_is_greater_2);
  tcase_add_test(tc_core, test_is_greater_3);
  tcase_add_test(tc_core, test_is_less_or_equal_1);
  tcase_add_test(tc_core, test_is_less_or_equal_2);
  tcase_add_test(tc_core, test_is_less_or_equal_3);
  tcase_add_test(tc_core, test_is_less_1);
  tcase_add_test(tc_core, test_is_less_2);
  tcase_add_test(tc_core, test_is_less_3);
  tcase_add_test(tc_core, test_is_equal_10);
  tcase_add_test(tc_core, test_is_not_equal_1);
  tcase_add_test(tc_core, test_is_not_equal_5);

  suite_add_tcase(s, tc_core);
  return s;
}