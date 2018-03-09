#ifndef TAYLOR_H
#define TAYLOR_H

double t_sin(double x); //Calculates Sin(x) using taylor polynomials with arbitrary precision.
double t_cos(double x); //Calculates Cos(x) using taylor polynomials with arbitrary precision.
double t_tan(double x); //Calculates Tan(x) using taylor polynomials with arbitrary precision.
double t_sqrt(double x);//Calculates sqrt(x) using taylor polynomials with arbitrary precision.

double power(double x, int p); //Calculates x^p, where p is an integer.

unsigned long factorial(unsigned long x); //Calculates x!

#endif
