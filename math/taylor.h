#ifndef TAYLOR_H
#define TAYLOR_H

double t_sin(double x); //Calculates Sin(x) using taylor polynomials
double t_cos(double x); //Calculates Cos(x) using taylor polynomials
double t_tan(double x); //Calculates Tan(x) using taylor polynomials
double t_sqrt(double x);//Calculates sqrt(x) using taylor polynomials
double t_atan(double x);//Calculates atan(x) using a finite series.
double t_atan2(double y, double x); //Calculates a quadrant-appropriate atan(x) using finite series
double t_exp(double x); //Calculates e^x using taylor polynomials
double power(double x, int p); //Calculates x^p, where p is an integer.
double absolute(double x);
unsigned long factorial(unsigned long x); //Calculates x!

#endif
