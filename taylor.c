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
double ttan(double x){
	return tsin(x)/tcos(x);
}

//Taylor approximation for square root
double t_sqrt(double x){
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
	sum *= a;
	/*if(sum <= 4 && sum >= 1){ //This sum is fairly inaccurate compared to the standard sqrt for numbers between 1 and 4
		long double difference = sum*sum - x;
		printf("diff: %Lf\n", difference/(a));
		return sum - difference;
	}*/
	return sum;
}

//Taylor approximation for atan
double t_atan(double x){
	
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
