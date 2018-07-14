#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "./matrix.h"
#include "./quadratic.h"
using std::cout;
using std::endl;
int main(int argc, char* argv[]){
	double a[2][2] = {
		{0, 1},
		{0, 0}
	};
	std::vector<double> eigen = Matrix(a).eigenvalues();
	for(int i = 0; i < eigen.size(); i++){
		cout << eigen[i] << endl;
	}
}
