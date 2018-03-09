#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "taylor.h"

clock_t start, end;
double time_used;

int main(int argc, char* argv[]){	
	double num = strtod(argv[1], NULL);
	
	printf("%f vs %f (%f)\n", sqrt(num), tsqrt(num), sqrt(num)-tsqrt(num));
}