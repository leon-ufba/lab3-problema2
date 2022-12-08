/*
 * cordic_fun.h
 *
  */
#include "cordic.h"
#ifndef CORDIC_FUN_H_
#define CORDIC_FUN_H_

void sin_cordic(real o);
void cos_cordic(real o);
void cosh_cordic(real o);
void sinh_cordic(real o);
void rect_cordic(real r, real o);
void pol_cordic(real x, real y);
void mul_cordic(real a, real b);
void div_cordic(real a, real b);

#endif /* CORDIC_FUN_H_ */
