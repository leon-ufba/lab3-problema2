#include <math.h>
#include <stdio.h>
#include "cordic.c"

// gdirection = {0: ROTATION, 1: VECTORING}
// gmode      = {0: CIRCULAR, 1: LINEAR, 2: HYPERBOLIC}

// seno
// cosseno
// seno hiperbólico
// cosseno hiperbólico
// conversão polar/retangular
// conversão retangular/polar
// multiplicação
// divisão

void sin_cordic(real o) {
  frac12 x1, y1, z1, x2, y2, z2;
  x1 = CIRCULAR_INV_K;
  y1 = 0;
  z1 = toFrac12(o);
  cordic(ROTATION, CIRCULAR, x1, y1, z1, &x2, &y2, &z2);
  printf(" => sin = (%04X) %f ~ %f\n", y2 & 0xFFFF, fromFrac12(y2), sin(o));
}

void cos_cordic(real o) {
  frac12 x1, y1, z1, x2, y2, z2;
  x1 = CIRCULAR_INV_K;
  y1 = 0;
  z1 = toFrac12(o);
  cordic(ROTATION, CIRCULAR, x1, y1, z1, &x2, &y2, &z2);
  printf(" => cos = (%04X) %f ~ %f\n", x2 & 0xFFFF, fromFrac12(x2), cos(o));
}

void sinh_cordic(real o) {
  frac12 x1, y1, z1, x2, y2, z2;
  x1 = HYPERBOLIC_INV_K;
  y1 = 0;
  z1 = toFrac12(o);
  cordic(ROTATION, HYPERBOLIC, x1, y1, z1, &x2, &y2, &z2);
  printf(" => sinh = (%04X) %f ~ %f\n", y2 & 0xFFFF, fromFrac12(y2), sinh(o));
}

void cosh_cordic(real o) {
  frac12 x1, y1, z1, x2, y2, z2;
  x1 = HYPERBOLIC_INV_K;
  y1 = 0;
  z1 = toFrac12(o);
  cordic(ROTATION, HYPERBOLIC, x1, y1, z1, &x2, &y2, &z2);
  printf(" => cosh = (%04X) %f ~ %f\n", x2 & 0xFFFF, fromFrac12(x2), cosh(o));
}

void rect_cordic(real r, real o) {
  frac12 x1, y1, z1, x2, y2, z2;
  x1 = toFrac12(r * REAL_CIRCULAR_INV_K);
  y1 = 0;
  z1 = toFrac12(o);
  cordic(ROTATION, CIRCULAR, x1, y1, z1, &x2, &y2, &z2);
  printf(" => rect = (%04X, %04X) [%f, %f] ~ [%f, %f]\n", x2 & 0xFFFF, y2 & 0xFFFF, fromFrac12(x2), fromFrac12(y2), r * cos(o), r * sin(o));
}

void pol_cordic(real x, real y) {
  frac12 x1, y1, z1, x2, y2, z2;
  x1 = toFrac12(x * REAL_CIRCULAR_INV_K);
  y1 = toFrac12(y * REAL_CIRCULAR_INV_K);
  z1 = 0;
  cordic(VECTORING, CIRCULAR, x1, y1, z1, &x2, &y2, &z2);
  printf(" => pol = (%04X, %04X) [%f, %f] ~ [%f, %f]\n", x2 & 0xFFFF, z2 & 0xFFFF, fromFrac12(x2), fromFrac12(z2), sqrt(x * x + y * y), atan(y / x));
}

void mul_cordic(real a, real b) {
  frac12 x1, y1, z1, x2, y2, z2;
  x1 = toFrac12(a);
  y1 = 0;
  z1 = toFrac12(b);
  cordic(ROTATION, LINEAR, x1, y1, z1, &x2, &y2, &z2);
  printf(" => mul = (%04X) %f ~ %f\n", y2 & 0xFFFF, fromFrac12(y2), a * b);
}

void div_cordic(real a, real b) {
  frac12 x1, y1, z1, x2, y2, z2;
  x1 = toFrac12(b);
  y1 = toFrac12(a);
  z1 = 0;
  cordic(VECTORING, LINEAR, x1, y1, z1, &x2, &y2, &z2);
  printf(" => div = (%04X) %f ~ %f\n", z2 & 0xFFFF, fromFrac12(z2), a / b);
}