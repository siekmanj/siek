#ifndef MATRIX_H
#define MATRIX_H
#include <stdlib.h>
#include <vector>

class Matrix{
  public:
    Matrix(int rows, int cols);
    Matrix(const Matrix& m);
    Matrix operator+(const Matrix&) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;
    Matrix operator*(double num) const;
    Matrix operator*(int num) const;
    Matrix operator=(const Matrix& m);
    Matrix submatrix(int row, int col);
    Matrix inverse();
    Matrix cofactor();
    Matrix transpose();
    Matrix rref();
    double determinant();
    double getIndex(int r, int c) const;

    int getRows() const;
    int getCols() const;
    int is_rref();
    
    std::vector<double> eigenvalues();

    void setIndex(double num, int r, int c);
    void printMatrix();

    ~Matrix();

    //Template implementation must be done in header
    template<int r, int c>
    Matrix(double (&arr)[r][c]){
      this->rows = r;
      this->cols = c;
      this->matrix = new double*[rows]; //Allocate row number of pointers the size of
      for(int i = 0; i < rows; i++){
        matrix[i] = new double[cols]; //create a double for every column in each row
        for(int j = 0; j < cols; j++){
          matrix[i][j] = arr[i][j];
        }
      }
    }


  private:
    double** matrix;
    int rows;
    int cols;
};
Matrix operator*(double k, const Matrix& m);
Matrix operator*(int k, const Matrix& m);


#endif
