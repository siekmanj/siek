#include "taylor.h"
#include <stdio.h>
const int PRECISION = 13;

//Taylor approximation for sin
double t_sin(double x){
	double sum = 0; //Initialize sum to 0
	for(int n = 0; n < PRECISION; n++){ //Sum PRECISION amount of polynomials together
		unsigned long factorial = 1; //Initialize factorial to 1
		double exponent = 1; //Initialize exponent to 1

		for(int i = 1; i <= 2*n+1; i++){
			exponent *= x; //Calculate x^(2n+1)
			factorial *= i; //Calculate (2n+1)!
		}
		if(n & 1){
			sum -= (double)exponent/(double)factorial; //If n is odd, subtract this term from the sum.
		}else{
			sum += (double)exponent/(double)factorial; //If n is even, add this term to the sum.
		}
	}
	return sum;
}

//Taylor approximation for sin
double t_cos(double x){
	double sum = 0; //Initialize sum to 0
	for(int n = 0; n < PRECISION; n++){ //Sum PRECISION amount of polynomials together

		unsigned long factorial = 1; //Initialize factorial to 1
		if(n & 1) factorial = -1;

		double exponent = 1; //Initialize exponent to 1

		for(int i = 1; i <= 2*n; i++){
			exponent *= x; //Calculate x^(2n)
			factorial *= i; //Calculate (2n)!
		}
		sum += (double)exponent/(double)factorial; //If n is even, add this term to the sum.
	}
	return sum;
}

//Taylor approximation for tan
double t_tan(double x){
	return t_sin(x)/t_cos(x);
}

//Taylor approximation for square root (still fairly inaccurate for values less than 0.5)
double t_sqrt(double x){
	long double sum = 0;
	unsigned long a;
	for(a = 1; a*a <= x; a++); //Increment until we get a square that is larger than x
	long double d = x - a*a; //Find the difference between the square and x

	if(absolute(x - (a-1)*(a-1)) < 0.00001){ //If the square before a is roughly equal to x,
		return a-1; // then return that instead of doing a ton of work
	}

	for(int n = 0; n < PRECISION; n++){
		long double numerator = (long double)factorial(2*n) * (long double)power(d, n); //(-1)^n * (2n)! * d^n
		if(n & 1) numerator *= -1;

		long double denominator = (1-2*n)*(double)factorial(n)*factorial(n)*power(4, n)*power(a, 2*n); //(1-2n)*(n!)^2*(4^n)*(a^2n)

		sum += numerator/denominator;
	}
	sum *= a;
	return sum;
}

//Technically not a Taylor approximation, but still a series that approximates atan
double t_atan(double x){
		double sum = 0;
		for(int n = 0; n < PRECISION; n++){
			long double numerator = power(x, 2*n+1);
			if(n & 1) numerator *= -1;
			sum += numerator / (2*n+1);
		}
		return sum;
}

double absolute(double x){
	if(x < 0) return -1*x;
	else return x;
}

//Calculates x^p, only works for integer powers
double power(double x, int p){
	double num = 1;
	for(int i = 0; i < p; i++) num *= x;
	return num;
}

//Calculates factorial given an integer.
unsigned long factorial(unsigned long x){
	unsigned long num = 1;
	for(int i = 1; i<=x; i++) num*=i;
	return num;
}
