/*
 * cordic.h
 *
 */
#include <stdint.h>
#ifndef CORDIC_H_
#define CORDIC_H_

typedef short int frac12;
typedef double real;      // change to modify float-point precision
//typedef unsigned int   uint16_t;

#define MY_PI 3.1415926536897932384626
#define REAL_HYPERBOLIC_INV_K 1.207497067763
#define REAL_LINEAR_INV_K     0.6072529350088812561694
#define REAL_CIRCULAR_INV_K   0.6072529350088812561694
#define HYPERBOLIC_INV_K 19783
#define LINEAR_INV_K     9949
#define CIRCULAR_INV_K   9949
#define CORDIC_NTAB 14
#define MUL (real)(1 << CORDIC_NTAB)

#define ROTATION   0
#define VECTORING  1

#define HYPERBOLIC 0
#define LINEAR     1
#define CIRCULAR   2

frac12 toFrac12(real v);
real fromFrac12(frac12 v);

void calcTable(uint16_t mode);
void calcK(frac12 mode);
void cordic(
  frac12 direction, frac12 mode,
  frac12 x, frac12 y, frac12 z,
  frac12* xout, frac12* yout, frac12* zout
);



#endif /* CORDIC_H_ */
