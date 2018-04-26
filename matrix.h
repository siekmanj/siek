#ifndef MATRIX_H
#define MATRIX_H
#include <stdlib.h>

class Matrix{
  public:
    Matrix(int rows, int cols);
    Matrix(const Matrix& m);
    //Matrix(Matrix m);
    //Matrix(double** m, int rows, int cols);
    Matrix operator+(const Matrix&) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;
    Matrix operator*(double num) const;
    Matrix inverse();
    Matrix cofactor();
    Matrix transpose();
    Matrix rref();
    double determinant();

    int getRows() const;
    int getCols() const;
    double getIndex(int r, int c) const;
    void setIndex(double num, int r, int c);

    void printMatrix();

    ~Matrix();

    //Template implementation must be done in header
    template<int r, int c>
    Matrix(double (&arr)[r][c]){
      this->rows = r;
      this->cols = c;
      this->matrix = (double **)malloc(rows*sizeof(double *)); //Allocate row number of pointers
      for(int i = 0; i < r; i++){
        matrix[i] = (double *)malloc(cols*sizeof(double)); //create a double for every column in each row
        for(int j = 0; j < c; j++){
          matrix[i][j] = arr[i][j];
        }
      }
    }


  private:
    int is_rref();
    double** matrix;
    int rows;
    int cols;
};
Matrix operator*(double k, const Matrix& m);

/*
double** create_matrix(int rows, int cols); //2D array containing a row*column matrix.
double** matrix_from_static_array(int rows, int cols, double input[][cols]); //Make a matrix from a static 2d array
double** copy_matrix(double** matrix, int rows, int cols); //Copy an existing matrix
void free_matrix(double **matrix, int rows, int cols); //Deallocate the memory of the matrix

void rref(double** matrix, int rows, int cols); //Convert a matrix to rref
void cofactor(double** matrix, int rows, int cols); //Convert a matrix into its cofactor matrix
void inverse(double** matrix, int rows, int cols); //Convert a matrix into its inverse
void transpose(double*** matrix, int rows, int cols); //Convert a matrix into its transpose (requires pointer to 2d array)


double determinant(double** matrix, int rows, int cols); //Calculate the determinant of a matrix

void print_matrix(double **matrix, int rows, int cols); //Prints a matrix to the terminal

int is_rref(double** matrix, int rows, int cols); //Checks to see if a matrix is in reduced row echelon form
*/
#endif
