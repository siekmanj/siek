#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "taylor.h"

clock_t start, end;
double time_used;
const double theta = 3.14159/4;
int main(int argc, char* argv[]){
	double num = strtod(argv[1], NULL);

	printf("%f vs %f (%f)\n", sqrt(num), t_sqrt(num), sqrt(num)-t_sqrt(num));
	//printf("%f vs %f (%f)\n", sin(num), t_sin(num), sin(num)-t_sin(num));
	//printf("%f vs %f (%f)\n", cos(num), t_cos(num), cos(num)-t_cos(num));

}
