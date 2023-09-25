#include <check.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "supp_func.h"
#include "tests.h"

int main() {
  Suite *tests[] = {dec_div_suite(),    dec_add_suite(),
                    int_to_dec_suite(), float_to_dec_suite(),
                    dec_mul_suite(),    dec_other_suite(),
                    dec_sub_suite(),    dec_mod_suite(),
                    dec_comp_suite(),   NULL};
  int no_failed = 0;
  for (int i = 0; tests[i]; ++i) {
    SRunner *runner;
    runner = srunner_create(tests[i]);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  if (no_failed == 0) printf("TEST OK\n");
  // double r;

  // printf("%lf", fmod(1.0, 0.003));

  //    s21_decimal dec1 = {0}, dec2 = {0};
  //    dec1.bits[0] = 1;
  //    set_exp(2, &dec2.bits[3]);
  //    dec2.bits[0] = 101;
  //        print_bits_decimal(&dec1);
  //        print_bits_decimal(&dec2);
  //    printf("rs = %d\n",s21_is_less_or_equal(dec1, dec2));
  //    s21_decimal dec1 = {0};
  //    s21_decimal dec2 = {0};
  //    s21_decimal ans;
  //    dec1.bits[0] = 532167;
  //    dec1.bits[3] = 196608;
  //    memset(&dec1, 0, 96);
  //
  //
  //    s21_decimal true_ans = {0};
  //    true_ans.bits[0] = 532167;
  //    true_ans.bits[3] = 196608;
  //    int res = s21_sub(dec1, dec2, &ans);
  //    print_bits_decimal(&dec1);
  //    print_bits_decimal(&dec2);
  //    print_bits_decimal(&ans);
  //    print_bits_decimal(&true_ans);

  //    s21_decimal dec1 = {0};
  //    s21_decimal dec2 = {0};
  //    s21_decimal ans;
  //
  //    dec1.bits[0] = 2891627761;
  //    dec1.bits[1] = 3474792174;
  //    dec1.bits[2] = 8;
  //    dec1.bits[3] = 2147811328;
  //    dec2.bits[0] = 1870970698;
  //    dec2.bits[1] = 1989793225;
  //    dec2.bits[3] = 720896;
  //    s21_decimal true_ans = {0};
  //    true_ans.bits[0] = 867247046;
  //    true_ans.bits[1] = 90;
  //    true_ans.bits[3] = 393216;
  //    true_ans.bits[0] = 1717205652;
  //    true_ans.bits[1] = 1236686312;
  //    set_exp(11, &true_ans.bits[3]);
  //    s21_negate(true_ans, &true_ans);
  //    int res = s21_mod(dec1, dec2, &ans);
  //    print_bits_decimal(&ans);
  //    print_bits_decimal(&true_ans);
  //    s21_decimal dec1 = {0};
  //    s21_decimal dec2 = {0};
  //    s21_decimal ans;
  //    dec1.bits[0] = 1996679748;
  //    dec1.bits[1] = 4232406046;
  //    dec1.bits[2] = 151016884;
  //    dec1.bits[3] = 2148335616;
  //    dec2.bits[0] = 2671657829;
  //    dec2.bits[1] = 165868194;
  //    dec2.bits[2] = 0;
  //    dec2.bits[3] = 327680;
  //    // -278576982813512.8359044835908 / 7123984713482.41253 =
  //    // -39.104096094745301845239149102
  //    //  79 228162514264337593543950335
  //    s21_decimal true_ans = {0};
  //    true_ans.bits[0] = 178532910;
  //    true_ans.bits[1] = 4081246736;
  //    true_ans.bits[2] = 2119837296;
  //    true_ans.bits[3] = 2149253120;
  //
  //    int res = s21_div(dec1, dec2, &ans);
  //    printf("res = %d\n", res);
  //    print_bits_decimal(&ans);
  //    print_bits_decimal(&true_ans);
  // printf("1 0000000 00011011 0000000000000000
  // 11111100101101000100110011100001111001101000010111000100001000000001010101001000011001000101110\n");
  //    s21_big_decimal tt, tt1, tt3;
  //    s21_big_decimal btt;
  //    s21_decimal d, d1, d2;
  //    memset(&d, 0, 16);
  //    memset(&d1, 0, 16);
  //    memset(&d2, 0, 16);
  ////
  ////    int gg = INT32_MIN;
  ////    int64_t ggg = gg;
  ////    ggg*=-1;
  ////    d.bits[0] = (uint32_t)ggg;
  ////    print_bits_decimal(&d);
  //    float a = 5.0, b = 3.0, c;
  //    c = a / b;
  //   // print_bits_float(c);
  //  //  printf("ost %lf", 1 % 0.0001);
  //
  //
  ////    print_bits_int(100);
  ////    printf("\n");
  ////    print_bits_int(1000);
  ////    printf("\n");
  ////    print_bits_int(10000);
  //    printf("%f\n", fmodf(0, 22) );
  //    memset(&btt, 0, 28);
  //    memset(&tt, 0, 28);
  //    memset(&tt1, 0, 28);
  //    memset(&tt3, 0, 28);
  //    s21_decimal aa = {0};
  //    s21_decimal bb = {0};
  //      s21_decimal res = {0};
  //      aa.bits[0] = 0b11111111111111111111111111111111;
  //      aa.bits[1] = 0b11111111111111111111111111111111;
  //      aa.bits[2] = 0b11111111111111111111111111111111;
  //      bb.bits[0] = 6;
  //      set_exp(1, &(bb.bits[3]));
  //    print_bits_decimal(&aa);
  //      s21_sub(aa, bb, &res);
  //    print_bits_decimal(&res);
  ////    s21_decimal tttt = {0};
  ////      float val = -9.99;
  ////      s21_from_float_to_decimal(val, &tttt);
  ////    print_bits_decimal(&tttt);
  ////      s21_floor(tttt, &tttt);
  ////    print_bits_decimal(&tttt);
  ////    tt3.bits[0] = 4294967295;
  ////    tt3.bits[1] = 4294967295;
  ////    tt3.bits[2] = 429496720;
  ////    tt1.bits[0] = 1;
  ////    int i = 0;
  ////    while (tt.bits[3] == 0 && i < 100000) {
  ////        print_bits_big_decimal(&tt3);
  ////        sum_equal_exp(tt1, tt3, &tt3, 191);
  ////        tt = tt3;
  ////        _x10(&tt);
  ////       // printf("%u\n",tt3.bits[2]);
  ////        tt3.bits[0] = 4294967295;
  ////        tt3.bits[1] = 4294967295;
  ////
  ////        ++i;
  ////    }
  ////    printf("%u\n",tt3.bits[2]);
  //  //  print_bits_big_decimal(&tt3);
  ////    tt.bits[0] = 0b01000110011001100110111110100101;
  ////    tt.bits[1] = 0b00000110011001110110001000100000;
  ////    tt.bits[2] = 0b00000000000000000000000000001001;
  ////    d.bits[0] = 1;
  ////    d1.bits[0] = 3;
  ////    //set_exp(1, &(d.bits[3]));
  ////    s21_div(d, d1, &d2);
  ////   // s21_add(d, d1, &d2);
  ////   print_bits_decimal(&d2);
  //  //  int v = 0;
  //  //  s21_from_decimal_to_int(d2, &v);
  //   // printf("v = %d\n", v);
  ////    d.bits[0] = 1666667;
  ////   // print_bits_decimal(&d);
  //////
  ////    tt1.bits[0] = 1;
  ////    for (int i = 0; i < 28; ++i)
  ////        _x10(&tt1);
  ////   // print_bits_big_decimal(&tt1);
  ////    printf ("err = %d\n", s21_from_float_to_decimal(c, &d1));
  ////    print_bits_decimal(&d1);
  ////    s21_from_decimal_to_float(d1, &c);
  ////    printf("%.7f\n", c);
  //////    s21_div_supp(tt, tt1, &tt3);
  //////    print_bits_big_decimal(&tt3);
  ////   // s21_negate(tt1, &tt1);
  ////    d.bits[0] = 10;
  ////    d1.bits[0] = 10;
  ////    set_exp(2, &d.bits[2]);
  ////    print_bits_decimal(&d);
  ////    s21_add(d, d1, &d2);
  ////    int v = 0;
  ////    int err = s21_from_decimal_to_int(d2, &v);
  ////    printf("err = %d  v = %d\n",err, v);
  //    // tt = s21_div_supp(tt, tt1, &tt3);
  ////    s21_div(d, d1, &d2);
  ////     print_bits_decimal(&d2);
  ////    s21_from_int_to_decimal(NAN, &d2);
  ////    print_bits_big_decimal(&tt3);
  ////    print_bits_big_decimal(&tt);
  ////    tt.bits[0] = 15;
  ////    tt1.bits[0] = 12;
  ////    minus_equal_exp(tt, tt1, &tt3);
  ////    print_bits_big_decimal(&tt);
  ////    print_bits_big_decimal(&tt1);
  ////    print_bits_big_decimal(&tt3);
  ////    while(tt.bits[2] <= 429496729) {
  ////        _x10(&tt);
  ////        print_bits_big_decimal(&tt);
  ////    }
  ////    shuffle_big_dec_right(&tt);
  //    //print_bits_big_decimal(&tt1);
  ////    btt.bits[0] = 1e10;
  ////    btt.bits[6] = -1;
  ////    print_bits_big_decimal(&btt);
  ////    btt = abs_big_decimal(btt);
  ////    print_bits_big_decimal(&btt);
  ////    set_bit(&tt.bits[3], 31, 1);
  ////    set_exp(28, &tt);
  ////    print_bits_decimal(&tt);
  ////    tt = abs_decimal(tt);
  ////    set_exp(1, &tt);
  ////    print_bits_decimal(&tt);
  ////    s21_negate(tt, &tt);
  ////    print_bits_decimal(&tt);
  ////    s21_negate(tt, &tt);
  ////    print_bits_decimal(&tt);
  ////    int i = get_sign(tt.bits[3]);
  ////    printf("sign = %d", i);
  ////    for (int i = 0; i < 34; ++i) {
  ////        shuffle_dec(&tt);
  ////        print_bits_decimal(&tt);
  ////    }
  ////    int flag = sum_equal_exp(tt, tt1, &tt3);
  ////   while(flag == 1) {
  ////        print_bits_decimal(&tt3);
  ////        flag = sum_equal_exp(tt3, tt3, &tt3);
  ////        print_bits_decimal(&tt3);
  ////    }
  ////    sum_equal_exp(tt3, tt3, &tt3);
  ////    print_bits_decimal(&tt3);
  ////    tt.bits[0] = 7;
  ////    while(_x10(&tt) == 1) {
  ////        print_bits_decimal(&tt);
  ////    }
  return 0;
}