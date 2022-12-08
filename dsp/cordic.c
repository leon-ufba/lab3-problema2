#include "cordic.h"
#include <math.h>
#include <stdio.h>
#ifndef __CORDIC__

#define __CORDIC__

// Cordic in 16 bit signed fixed point math
// Function is valid for arguments in range -pi/2 -- pi/2
// for values pi/2--pi: value = half_pi-(theta-half_pi) and similarly for values -pi---pi/2
// 1.0 = 16384
// 1/k = 0.6072529350088812561694
// pi = 3.1415926536897932384626
// fixed-point = Q2.14S


frac12 cordic_tab[3][16] = {
  { 32000, 8999, 4184, 2058, 1025, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1, 0 }, /* HYPERBOLIC */  //
  { 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1, 0 }, /* LINEAR     */
  { 12867, 7596, 4013, 2037, 1022, 511, 255, 127, 63, 31, 15, 7, 3, 1, 0, 0 }  /* CIRCULAR   */
};

frac12 cordic_coef[3] = {
  -1, /* HYPERBOLIC */
   0, /* LINEAR     */
   1, /* CIRCULAR   */
};

frac12 cordic_steps[3][16] = {
  { 1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 13, 14 }, /* HYPERBOLIC */  // for convergence in hyperbolic mode, steps 4 and 13 must be repeated
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, /* LINEAR     */
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }  /* CIRCULAR   */
};

frac12 toFrac12(real v) {
  return (frac12)(v * MUL);
}

real fromFrac12(frac12 v) {
  return (real)(v / MUL);
}



void calcTable(uint16_t mode) {
  uint16_t i;
  real r, a;
  frac12 f;
  for ( i = 0; i < 16; i++) {
    r = pow(2, -i);
    a = (mode == HYPERBOLIC) ? atanh(r) : (mode == CIRCULAR) ? atan(r) : r;
    f = toFrac12(a);
    printf("a(%f) = %f =>  %f  %d\n", r, a, fromFrac12(f), f);
  }
}

void calcK(frac12 mode) {
  real k = 1;
  frac12 step;
  uint16_t i, i_end;
  if(mode != HYPERBOLIC) {
    i_end = CORDIC_NTAB;
    for (i = 0; i < i_end; i++) {
      step = cordic_steps[mode][i];
      k *= sqrt(1.0 + pow(2.0, -2 * step));
    }
  } else {
    i_end = CORDIC_NTAB + 1;
    for (i = 0; i < i_end; i++) {
      step = cordic_steps[mode][i];
      k *= sqrt(1.0 - pow(2.0, -2 * step));
    }
  }
  k = 1.0 / (k);
  frac12 f = toFrac12(k);
  printf("1/K(%d) = %f =>  %f  %d\n", i_end, k, fromFrac12(f), f);
}

void cordic(
  frac12 direction, frac12 mode,
  frac12 x, frac12 y, frac12 z,
  frac12* xout, frac12* yout, frac12* zout
) {
  frac12 d, u, step, ai, xi, yi;
  uint16_t i, i_end;

  i_end = ((mode != HYPERBOLIC) ? CORDIC_NTAB : CORDIC_NTAB + 1);
  for (i = 0; i < i_end; i++) {
    step = cordic_steps[mode][i];
    ai   = cordic_tab[mode][step];
    u    = cordic_coef[mode];

    d  = ((direction == ROTATION) ? ((z >= 0) ? 1 : -1) : ((x >= 0) ? ((y >= 0) ? -1 : 1): ((y >= 0) ? 1 : -1)));
    yi = (y >> step);
    xi = (x >> step);

    if(d == 1) {
      yi = (u > 0) ? -yi : (u < 0) ? yi : 0;
      ai = -ai;
    } else {
      yi = (u > 0) ? yi : (u < 0) ? -yi : 0;
      xi = -xi;
    }

    x += yi;
    y += xi;
    z += ai;
  }

  *xout = x;
  *yout = y;
  *zout = z;
}

#endif
