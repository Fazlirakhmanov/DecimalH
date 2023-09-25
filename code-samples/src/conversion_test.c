#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "supp_func.h"

START_TEST(s21_fl_to_dec_1) {
  s21_decimal decimal = {0};
  float number = 1356.22;
  s21_from_float_to_decimal(number, &decimal);
}
END_TEST

START_TEST(s21_fl_to_dec_2) {
  s21_decimal decimal = {0};
  float A = 100.532;
  float B = 0.0;
  s21_from_float_to_decimal(A, &decimal);
  s21_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(s21_fl_to_dec_3) {
  s21_decimal decimal = {0};
  float A = -100.532;
  float B = 0.0;
  s21_from_float_to_decimal(A, &decimal);
  s21_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(A, B);
}
END_TEST

START_TEST(s21_fl_to_dec_4) {
  s21_decimal decimal = {0};
  float A = -10000.121;
  float B = 0.0;
  s21_from_float_to_decimal(A, &decimal);
  s21_from_decimal_to_float(decimal, &B);
  ck_assert_float_eq(-10000.12, B);
}
END_TEST

Suite *float_to_dec_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_float_to_dec");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_fl_to_dec_1);
  tcase_add_test(tc_core, s21_fl_to_dec_2);
  tcase_add_test(tc_core, s21_fl_to_dec_3);
  tcase_add_test(tc_core, s21_fl_to_dec_4);
  // tcase_add_test(tc_core, s21_div_2);
  suite_add_tcase(s, tc_core);
  return s;
}

//------------------------dec_to_int_to_dec-------------------------

START_TEST(s21_int_to_dec) {
  s21_decimal dec1;
  //  int src;
  //  memset(&dec1, 0, 16);
  // src = NAN;
  s21_from_int_to_decimal(5, &dec1);
  ck_assert_uint_eq(dec1.bits[0], 5);
  ck_assert_uint_eq(dec1.bits[1], 0);
  ck_assert_uint_eq(dec1.bits[2], 0);
  ck_assert_uint_eq(dec1.bits[3], 0);
  s21_from_int_to_decimal(-5, &dec1);
  ck_assert_uint_eq(dec1.bits[0], 5);
  ck_assert_uint_eq(dec1.bits[1], 0);
  ck_assert_uint_eq(dec1.bits[2], 0);
  ck_assert_int_eq(get_sign(dec1.bits[3]), 1);
}
END_TEST
START_TEST(s21_dec_to_int) {
  s21_decimal dec1;
  int res;
  memset(&dec1, 0, 16);
  s21_from_int_to_decimal(-5, &dec1);
  s21_from_decimal_to_int(dec1, &res);
  ck_assert_int_eq(res, -5);
  s21_from_int_to_decimal(55555, &dec1);
  set_exp(4, &(dec1.bits[3]));
  s21_from_decimal_to_int(dec1, &res);
  ck_assert_int_eq(res, 5);
}
START_TEST(s21_int_to_dec_1) {
  s21_decimal dec = {0};
  int i = INT32_MAX, res = 0;
  s21_from_int_to_decimal(i, &dec);
  s21_from_decimal_to_int(dec, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(s21_int_to_dec_2) {
  s21_decimal dec = {0};
  int i = INT32_MIN, res = 0;
  s21_from_int_to_decimal(i, &dec);
  s21_from_decimal_to_int(dec, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

/* FROM DECIMAL TO FLOAT */
START_TEST(from_decimal_to_float_1) {
  s21_decimal a;
  float res = 0.0;
  a.bits[0] = 1234567;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 3;
  s21_from_decimal_to_float(a, &res);
  ck_assert_float_eq_tol(res, 1234.567, 1e7);
}
END_TEST

START_TEST(from_decimal_to_float_2) {
  s21_decimal a;
  float res = 0.0;
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;
  a.bits[3] = 0;
  ck_assert_int_eq(s21_from_decimal_to_float(a, &res), 0);
  ck_assert_float_eq(res, 79228162514264337593543950336.0f);
}
END_TEST

START_TEST(from_decimal_to_float_4) {
  s21_decimal a;
  float res = 0.0;
  a.bits[0] = 1905;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 2147483648;
  ck_assert_int_eq(s21_from_decimal_to_float(a, &res), 0);
  ck_assert_float_eq(res, -1905);
}
END_TEST

START_TEST(from_decimal_to_float_5) {
  s21_decimal a;
  float res = 0.0;
  a.bits[0] = 0xFFFFF;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  ck_assert_int_eq(s21_from_decimal_to_float(a, &res), 0);
  ck_assert_float_eq(res, 1048575);
}
END_TEST

START_TEST(from_decimal_to_float_10) {
  s21_decimal a;
  float res = 0.0;
  a.bits[0] = 0;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 2147483648;
  ck_assert_int_eq(s21_from_decimal_to_float(a, &res), 0);
  ck_assert_float_eq(res, -0);
}
END_TEST

START_TEST(from_decimal_to_float_11) {
  s21_decimal a;
  float res = 0.0;
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 2147483648;
  ck_assert_int_eq(s21_from_decimal_to_float(a, &res), 0);
  ck_assert_float_eq(res, -4294967295);
}
END_TEST

START_TEST(from_decimal_to_float_12) {
  s21_decimal a;
  float res = 0.0;
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 2147483648;
  ck_assert_int_eq(s21_from_decimal_to_float(a, &res), 0);
  ck_assert_float_eq(res, -4294967295);
}
END_TEST

START_TEST(from_decimal_to_float_14) {
  s21_decimal a;
  float res = 0.0;
  a.bits[0] = 0b00000000010100111001000011000010;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b00000000000000010000000000000000;
  ck_assert_int_eq(s21_from_decimal_to_float(a, &res), 0);
  ck_assert_float_eq_tol(res, 54675.46, 1e7);
}
END_TEST

START_TEST(from_decimal_to_float_15) {
  s21_decimal a;
  float res = 0.0;
  a.bits[0] = 0b00000000000000001011010101110101;
  a.bits[1] = 0b00000000000000000000000000000000;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b10000000000001010000000000000000;
  ck_assert_int_eq(s21_from_decimal_to_float(a, &res), 0);
  ck_assert_float_eq(res, -0.46453);
}
END_TEST

START_TEST(from_decimal_to_float_16) {
  s21_decimal a;
  float res = 0;
  a.bits[0] = 0b01100101101110011011001110011111;
  a.bits[1] = 0b00000000000000000000000010000011;
  a.bits[2] = 0b00000000000000000000000000000000;
  a.bits[3] = 0b00000000000010010000000000000000;
  s21_from_decimal_to_float(a, &res);
  ck_assert_float_eq_tol(res, 564.3473, 1e7);
}
END_TEST

/* FROM DECIMAL TO INT */

START_TEST(from_decimal_to_int_2) {
  s21_decimal a;
  int n = 0;
  int res = 0;
  a.bits[0] = 133141;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0;
  res = s21_from_decimal_to_int(a, &n);
  ck_assert_int_eq(n, 133141);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_decimal_to_int_4) {
  s21_decimal a;
  int n = 0;
  int res = 0;
  a.bits[0] = 123451234;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 2147483648;
  res = s21_from_decimal_to_int(a, &n);
  ck_assert_int_eq(n, -123451234);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_decimal_to_int_5) {
  s21_decimal a;
  int n = 0;
  int res = 0;
  a.bits[0] = 18;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 2147483648;
  res = s21_from_decimal_to_int(a, &n);
  ck_assert_int_eq(n, -18);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_decimal_to_int_6) {
  s21_decimal a;
  int n = 0;
  int res = 0;
  a.bits[0] = 4294967295;
  a.bits[1] = 4294967295;
  a.bits[2] = 0;
  a.bits[3] = 0;
  res = s21_from_decimal_to_int(a, &n);
  ck_assert_int_eq(n, 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

/* FROM FLOAT TO DECIMAL */
START_TEST(from_float_to_decimal_1) {
  s21_decimal a = {{0x00000C8C, 0, 0, 0x80010000}};
  s21_decimal b = {{0, 0, 0, 0}};
  float n = -321.2;
  int res = s21_from_float_to_decimal(n, &b);
  ck_assert_int_eq(b.bits[0], a.bits[0]);
  ck_assert_int_eq(b.bits[1], a.bits[1]);
  ck_assert_int_eq(b.bits[2], a.bits[2]);
  ck_assert_int_eq(b.bits[3], a.bits[3]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  s21_decimal a = {{0x00000C8C, 0, 0, 0x00010000}};
  s21_decimal b = {{0, 0, 0, 0}};
  float n = 321.2;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_3) {
  s21_decimal a = {{0x13255310, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  float n = 321213143.8323;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_4) {
  s21_decimal a = {{0xC7238000, 0x9472ED75, 0x0000020F, 0}};
  s21_decimal b = {0};
  float n = 9732131234575756436473.323123474;
  int res = s21_from_float_to_decimal(n, &b);
  ck_assert_int_eq(b.bits[0], a.bits[0]);
  ck_assert_int_eq(b.bits[1], a.bits[1]);
  ck_assert_int_eq(b.bits[2], a.bits[2]);
  ck_assert_int_eq(b.bits[3], a.bits[3]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_5) {
  s21_decimal a = {{0x006FE484, 0, 0, 0x00050000}};
  s21_decimal b = {0};
  float n = 73.329959999;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_6) {
  s21_decimal a = {{0x00000003, 0, 0, 0x00030000}};
  s21_decimal b = {0};
  float n = 0.003;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_7) {
  s21_decimal a = {{0x0004C419, 0, 0, 0x00080000}};
  s21_decimal b = {0};
  float n = 0.00312345;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_8) {
  s21_decimal a = {{0x0004C44C, 0, 0, 0x000D0000}};
  s21_decimal b = {0};
  float n = 0.00000003123959595945;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_9) {
  s21_decimal a = {{0x008F532B, 0, 0, 0x00180000}};
  s21_decimal b = {0};
  float n = 0.0000000000000000093929383838292;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_10) {
  s21_decimal a = {{0x00000001, 0, 0, 0x001C0000}};
  s21_decimal b = {0};
  float n = 0.00000000000000000000000000013929383838292;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_11) {
  s21_decimal a = {{0x00000002, 0, 0, 0x001C0000}};
  s21_decimal b = {0};
  float n = 0.00000000000000000000000000016929383838292;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_12) {
  s21_decimal a = {0};
  float n = .00000000000000000000000000000000193929383838292;
  int res = s21_from_float_to_decimal(n, &a);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(from_float_to_decimal_13) {
  s21_decimal a = {{0x8ADB0000, 0x59BC8E01, 0x00000076, 0}};
  s21_decimal b = {0};
  float n = 2183182381923912939123.365656f;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_14) {
  s21_decimal a = {{0xCF000000, 0xAC05AE5D, 0xFFF51CBA, 0}};
  s21_decimal b = {0};
  float n = 79215000000000000000000000000.365656;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_15) {
  s21_decimal a = {{0xC7000000, 0xFFD18396, 0x16AAAC07, 0}};
  s21_decimal b = {0};
  float n = 7015000000000000000000000000.365656;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_16) {
  s21_decimal a = {{0x00000235, 0, 0, 0x001C0000}};
  s21_decimal b = {0};
  float n = 0.00000000000000000000000005646473736464;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_17) {
  s21_decimal a = {{0x00001CCE, 0, 0, 0x001C0000}};
  s21_decimal b = {0};
  float n = 0.00000000000000000000000073736361612636;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_18) {
  s21_decimal a = {{0x0000218A, 0, 0, 0x001B0000}};
  s21_decimal b = {0};
  float n = 0.00000000000000000000000858598287381972;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(from_float_to_decimal_19) {
  s21_decimal a = {{0x00000001, 0, 0, 0x00160000}};
  s21_decimal b = {0};
  float n = 0.000000000000000000000099999999999;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(from_float_to_decimal_20) {
  s21_decimal a = {{0x00708F1B, 0, 0, 0x001C0000}};
  s21_decimal b = {0};
  float n = 0.00000000000000000000073766666662636;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(from_float_to_decimal_21) {
  s21_decimal a = {{0x00708344, 0, 0, 0x001B0000}};
  s21_decimal b = {0};
  float n = 0.0000000000000000000073736361612636;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(from_float_to_decimal_22) {
  s21_decimal a = {{0x00001CCE, 0, 0, 0x001C0000}};
  s21_decimal b = {0};
  float n = 0.00000000000000000000000073736361612636;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_23) {
  s21_decimal a = {{0x00C78EA4, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal b = {0};
  float n = -1.307818E+07;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_24) {
  s21_decimal a = {{0x002F2C14, 0x00000000, 0x00000000, 0x80020000}};
  s21_decimal b = {0};
  float n = -30914.76;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_25) {
  s21_decimal a = {{0x000000C5, 0x00000000, 0x00000000, 0x001C0000}};
  s21_decimal b = {0};
  float n = 1.965111E-26;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_26) {
  s21_decimal a = {{0x00729790, 0x00000000, 0x00000000, 0x80040000}};
  s21_decimal b = {0};
  float n = -750.9904;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(from_float_to_decimal_27) {
  s21_decimal a = {{0x000B20EA, 0x00000000, 0x00000000, 0x00010000}};
  s21_decimal b = {0};
  float n = 72932.2;
  int res = s21_from_float_to_decimal(n, &b);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(b.bits[i], a.bits[i]);
  ck_assert_int_eq(res, 0);
}
END_TEST

/* FROM INT TO DECIMAL */
START_TEST(from_int_to_decimal_1) {
  s21_decimal a;
  s21_from_int_to_decimal(0, &a);
  ck_assert_int_eq(a.bits[0], 0);
  ck_assert_int_eq(a.bits[1], 0);
  ck_assert_int_eq(a.bits[2], 0);
  ck_assert_int_eq(a.bits[3], 0);
}
END_TEST

START_TEST(from_int_to_decimal_2) {
  s21_decimal a;
  s21_from_int_to_decimal(-1, &a);
  ck_assert_int_eq(a.bits[0], 1);
  ck_assert_int_eq(a.bits[1], 0);
  ck_assert_int_eq(a.bits[2], 0);
  ck_assert_int_eq((int)a.bits[3], -2147483648);
}
END_TEST

START_TEST(from_int_to_decimal_3) {
  s21_decimal a;
  s21_from_int_to_decimal(1, &a);
  ck_assert_int_eq(a.bits[0], 1);
  ck_assert_int_eq(a.bits[1], 0);
  ck_assert_int_eq(a.bits[2], 0);
  ck_assert_int_eq(a.bits[3], 0);
}
END_TEST

START_TEST(from_int_to_decimal_4) {
  s21_decimal a;
  s21_from_int_to_decimal(-2147483648, &a);
  ck_assert_int_eq((int)a.bits[0], -2147483648);
  ck_assert_int_eq(a.bits[1], 0);
  ck_assert_int_eq(a.bits[2], 0);
  ck_assert_int_eq((int)a.bits[3], -2147483648);
}
END_TEST

START_TEST(from_int_to_decimal_5) {
  s21_decimal a;
  s21_from_int_to_decimal(123456789, &a);
  ck_assert_int_eq((int)a.bits[0], 123456789);
  ck_assert_int_eq(a.bits[1], 0);
  ck_assert_int_eq(a.bits[2], 0);
  ck_assert_int_eq(a.bits[3], 0);
}
END_TEST

Suite *int_to_dec_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_int_to_dec");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_int_to_dec);
  tcase_add_test(tc_core, s21_dec_to_int);
  tcase_add_test(tc_core, s21_int_to_dec_1);
  tcase_add_test(tc_core, s21_int_to_dec_2);
  tcase_add_test(tc_core, from_decimal_to_float_1);
  tcase_add_test(tc_core, from_decimal_to_float_2);
  tcase_add_test(tc_core, from_decimal_to_float_4);
  tcase_add_test(tc_core, from_decimal_to_float_5);
  tcase_add_test(tc_core, from_decimal_to_float_10);
  tcase_add_test(tc_core, from_decimal_to_float_11);
  tcase_add_test(tc_core, from_decimal_to_float_12);
  tcase_add_test(tc_core, from_decimal_to_float_14);
  tcase_add_test(tc_core, from_decimal_to_float_15);
  tcase_add_test(tc_core, from_decimal_to_float_16);
  tcase_add_test(tc_core, from_decimal_to_int_2);
  tcase_add_test(tc_core, from_decimal_to_int_4);
  tcase_add_test(tc_core, from_decimal_to_int_5);
  tcase_add_test(tc_core, from_decimal_to_int_6);
  tcase_add_test(tc_core, from_float_to_decimal_1);
  tcase_add_test(tc_core, from_float_to_decimal_2);
  tcase_add_test(tc_core, from_float_to_decimal_3);
  tcase_add_test(tc_core, from_float_to_decimal_4);
  tcase_add_test(tc_core, from_float_to_decimal_5);
  tcase_add_test(tc_core, from_float_to_decimal_6);
  tcase_add_test(tc_core, from_float_to_decimal_7);
  tcase_add_test(tc_core, from_float_to_decimal_8);
  tcase_add_test(tc_core, from_float_to_decimal_9);
  tcase_add_test(tc_core, from_float_to_decimal_10);
  tcase_add_test(tc_core, from_float_to_decimal_11);
  tcase_add_test(tc_core, from_float_to_decimal_12);
  tcase_add_test(tc_core, from_float_to_decimal_13);
  tcase_add_test(tc_core, from_float_to_decimal_14);
  tcase_add_test(tc_core, from_float_to_decimal_15);
  tcase_add_test(tc_core, from_float_to_decimal_16);
  tcase_add_test(tc_core, from_float_to_decimal_17);
  tcase_add_test(tc_core, from_float_to_decimal_18);
  tcase_add_test(tc_core, from_float_to_decimal_19);
  tcase_add_test(tc_core, from_float_to_decimal_20);
  tcase_add_test(tc_core, from_float_to_decimal_21);
  tcase_add_test(tc_core, from_float_to_decimal_22);
  tcase_add_test(tc_core, from_float_to_decimal_23);
  tcase_add_test(tc_core, from_float_to_decimal_24);
  tcase_add_test(tc_core, from_float_to_decimal_25);
  tcase_add_test(tc_core, from_float_to_decimal_26);
  tcase_add_test(tc_core, from_float_to_decimal_27);
  tcase_add_test(tc_core, from_int_to_decimal_1);
  tcase_add_test(tc_core, from_int_to_decimal_2);
  tcase_add_test(tc_core, from_int_to_decimal_3);
  tcase_add_test(tc_core, from_int_to_decimal_4);
  tcase_add_test(tc_core, from_int_to_decimal_5);
  suite_add_tcase(s, tc_core);
  return s;
}