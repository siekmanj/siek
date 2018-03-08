#include "taylor.h"
#include <stdio.h>

const int PRECISION = 13;

//const double PI = 3.141592653589793238462643383279502884;

//Taylor approximation for sin
double tsin(double x){
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
double tcos(double x){
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
double ttan(double x){
	return tsin(x)/tcos(x);
}

//Taylor approximation for square root
double tsqrt(double x){
	long double sum = 0;
	unsigned long a;
	
	for(a = 1; a*a <= x; a++);
	long double d = x - a*a;
	for(int n = 0; n < PRECISION; n++){
		long double numerator = 1;
		if(n & 1) numerator = -1;
		long double denominator;
	
		numerator *= (long double)factorial(2*n) * (long double)power(d, n);
		denominator = (1-2*n)*(double)factorial(n)*factorial(n)*power(4, n)*power(a, 2*n);
		sum += numerator/denominator;
	}
	return sum * a; 
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
