#include <stdio.h>
#include <stdint.h>
#include "cordic_fun.h"
#include "cordic.h"

int main(int argc, char **argv) {

  real steps;
  real limit;
  real i;
  real r, o; // POLAR
  real x, y; // RECTANGULAR
  real a, b; // ARITHMETIC

  printf("\nSIN\n");
  steps = 8;
  limit = steps;
  for (i = 0; i <= limit; i++) {
     o = (i / steps) * MY_PI / 2;
    printf("pi * %.0f/%.0f = %f", i, steps, o);
    sin_cordic(o);
  }

  printf("\nCOS\n");
  steps = 8;
  limit = steps;
  for (i = 0; i <= limit; i++) {
     o = (i / steps) * MY_PI / 2;
    printf("pi * %.0f/%.0f = %f", i, steps, o);
    cos_cordic(o);
  }

  printf("\nSINH\n");
  steps = 8;
  limit = steps;
  for (i = 0; i <= limit; i++) {
     o = (i / steps) * MY_PI / 2;
    printf("pi * %.0f/%.0f = %f", i, steps, o);
    sinh_cordic(o);
  }

  printf("\nCOSH\n");
  steps = 8;
  limit = steps;
  for (i = 0; i <= limit; i++) {
     o = (i / steps) * MY_PI / 2;
    printf("pi * %.0f/%.0f = %f", i, steps, o);
    cosh_cordic(o);
  }

  printf("\nRECT\n");
  limit = 0.5;
  for (r = 0.1; r <= limit; r+=0.1) {
    for (o = 0.1; o <= limit; o+=0.1) {
      printf("[%f, %f]", r, o);
      rect_cordic(r, o);
    }
  }

  printf("\nPOL\n");
  limit = 0.5;
  for (x = 0.1; x <= limit; x+=0.1) {
    for (y = 0.1; y <= limit; y+=0.1) {
      printf("[%f, %f]", x, y);
      pol_cordic(x, y);
    }
  }

  printf("\nMUL\n");
  limit = 1.0;
  for (i = 0; i < steps; i++) { limit /= 2.0; }
  for (a = 1.0; a >= limit; a/=2.0) {
    for (b = 1.0; b >= limit; b/=2.0) {
      printf("%f * %f", a, b);
      mul_cordic(a, b);
    }
  }

  printf("\nDIV\n");
  limit = 1.0;
  a = 1.0 / 8.0;
  for (b = a; b <= limit; b += a) {
    printf("%f / %f", a, b);
    div_cordic(a, b);
  }

  printf("\nSUCCESSFULLY FINISHED!\n");
  return 0;
}
