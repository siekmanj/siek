#include "./taylor.h"
#include <stdio.h>
const int PRECISION = 15;
const long double PI = 3.1415926535897932384626433832795028841971693993751058209;

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
		double exponent = 1; //Initialize exponent to 1

		for(int i = 1; i <= 2*n; i++){
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

	if(absolute(x - (a-1)*(a-1)) < 0.00001){ //Special case: if a^2 is x
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
double t_exp(double x){
	long double sum = 0;
	long double a = 10*x;

	for(int n = 0; n < PRECISION; n++){
		sum += (long double)power(x, n)/(long double)factorial(n);
	}
	return sum;
}
double t_atan2(double y, double x){
	double arc_tangent = t_atan(y/x);
	if(x < 0){
		if(arc_tangent < 0) arc_tangent += PI;
		if(arc_tangent > 0) arc_tangent -= PI;
	}
	return arc_tangent;
}
//Technically not a Taylor approximation, but still a series that approximates atan (badly)
double t_atan(double x){
		double sum = 0;
		int inversion = 1;

		//If abs(x) > 1, the infinite series will diverge and we will get an unreasonable number.
		//To account for this, we swap x to 1/x. This essentially mirrors the angle to the other side of the 45-degree line.
		//If that doesn't make sense, think of it as y/x -> x/y.
		//We then have to subtract the sum from +/- pi/2, instead of adding it to 0.
		if(x > 1){
			x = 1/x;
			sum = PI/2;
			inversion = -1;
		}
		//Also need to account for x < -1 for same reason
		if(x < -1){
			x = 1/x;
			sum = -PI/2;
			inversion = -1;
		}

		//Special case when x is close to 1 (precision tends to be very poor for values close to 1)
		if(absolute(x - 1) < 0.000001) return PI/4;
		if(absolute(x + 1) < 0.000001) return -PI/4;

		for(int n = 0; n < PRECISION; n++){
			long double numerator = power(x, 2*n+1); //x^2n+1
			if(n & 1) numerator *= -1; //(-1)^n
			long double denominator = (2*n+1);

			sum += inversion * numerator / denominator;
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
