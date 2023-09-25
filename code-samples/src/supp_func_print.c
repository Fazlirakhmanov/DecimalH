#include <stdio.h>

#include "supp_func.h"

void print_bits_float(float val) {
  union {
    float f;
    int i;
  } u;
  u.f = val;
  char buff[32];
  int i = 31;
  while (i >= 0) {
    if (u.i & 1)
      buff[i] = '1';
    else
      buff[i] = '0';
    u.i >>= 1;
    --i;
  }
  printf("sign: %c\n exp: ", buff[0]);
  for (int i = 1; i < 32; ++i) {
    printf("%c ", buff[i]);
    i == 8 ? printf("\nmant: ") : 1;
  }
  printf("\n");
}

void print_bits_int(int val) {
  int ind = 31;
  while (ind >= 0) {
    if (val & (1 << ind))
      printf("1");
    else
      printf("0");
    --ind;
  }
  printf(" ");
}
void print_bits_decimal(const s21_decimal *dst) {
  for (int i = 3; i >= 0; --i) {
    int ind = 31;
    while (ind >= 0) {
      if (dst->bits[i] & (1 << ind))
        printf("1");
      else
        printf("0");
      --ind;
      if (i == 3 && (ind == 15 || ind == 23 || ind == 30)) printf(" ");
    }
    printf(" ");
  }
  printf("\n");
}
void print_bits_big_decimal(const s21_big_decimal *dst) {
  for (int i = 6; i >= 0; --i) {
    int ind = 31;
    if (i <= 3 || i == 6) {
      while (ind >= 0) {
        if (dst->bits[i] & (1 << ind))
          printf("1");
        else
          printf("0");
        --ind;
        if (i == 6 && (ind == 15 || ind == 23 || ind == 30)) printf(" ");
      }
      printf(" ");
    }
  }
  printf("\n");
}
