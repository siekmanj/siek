#ifndef MATRIX_H
#define MATRIX_H

double** create_matrix(int rows, int cols); //2D array containing a row*column matrix.
double** matrix_from_static_array(int rows, int cols, double input[][cols]); //Make a matrix from a static 2d array
void free_matrix(double **matrix, int rows, int cols); //Deallocate the memory of the matrix

void rref(double** matrix, int rows, int cols); //Convert a matrix to rref

double determinant(double** matrix, int rows, int cols); //Calculate the determinant of a matrix

void print_matrix(double **matrix, int rows, int cols); //Prints a matrix to the terminal

int is_rref(double** matrix, int rows, int cols); //Checks to see if a matrix is in reduced row echelon form
#endif
