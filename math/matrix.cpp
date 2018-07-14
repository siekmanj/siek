#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "./matrix.h"
#include "./quadratic.h"
using std::cout;
using std::endl;

Matrix::Matrix(int rows, int cols){
  this->rows = rows;
  this->cols = cols;
  this->matrix = new double*[rows]; //Allocate pointers each the size of a row
  for(int i = 0; i < rows; i++){
    matrix[i] = new double[cols]; //create a double for every number in each row
    for(int j = 0; j < cols; j++){
      matrix[i][j] = 0;
    }
  }
}
Matrix::Matrix(const Matrix& m){
  this->rows = m.rows;
  this->cols = m.cols;
  this->matrix = new double*[rows]; //Allocate pointers each the size of a row
  for(int i = 0; i < rows; i++){
    matrix[i] = new double[cols]; //create a double for every number in each row
    for(int j = 0; j < cols; j++){
      matrix[i][j] = m.matrix[i][j];
    }
  }
}

Matrix::~Matrix(){
  for(int i = 0; i < rows; i++){
    delete [] matrix[i];
  }
  delete [] matrix;
}

Matrix Matrix::operator+(const Matrix& m) const{
  if(this->cols != m.cols || this->rows != m.rows){
    printf("Bad dims\n");
    return *this;
  }
  Matrix result = Matrix(this->rows, this->cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < rows; j++){
      result.matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];
    }
  }
  return result;
}

Matrix Matrix::operator-(const Matrix& m) const{
  if(this->cols != m.cols || this->rows != m.rows){
    printf("Bad dims\n");
    return *this;
  }
  Matrix result = Matrix(this->rows, this->cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < rows; j++){
      result.matrix[i][j] = this->matrix[i][j] - m.matrix[i][j];
    }
  }
  return result;
}

Matrix Matrix::operator*(const Matrix& m) const{
  if(cols != m.rows){
    printf("Bad dims\n");
    return *this;
  }
  Matrix result = Matrix(rows, m.cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < m.cols; j++){
      double sum = 0;
      for(int k = 0; k < m.rows; k++){
        sum += matrix[i][k] * m.matrix[k][j];
      }
      result.matrix[i][j] = sum;
    }
  }
  return result;
}

Matrix Matrix::operator*(double num) const{
  Matrix result = Matrix(rows, cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      result.matrix[i][j] = matrix[i][j] * num;
    }
  }
  return result;
}
Matrix Matrix::operator*(int num) const{
  Matrix result = Matrix(rows, cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      result.matrix[i][j] = matrix[i][j] * num;
    }
  }
  return result;
}

Matrix operator*(double num, const Matrix& m){
  double rows = m.getRows();
  double cols = m.getCols();
  Matrix result = Matrix(rows, cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      result.setIndex(m.getIndex(i, j)*num, i, j);
    }
  }
  return result;
}
Matrix operator*(int num, const Matrix& m){
  double rows = m.getRows();
  double cols = m.getCols();
  Matrix result = Matrix(rows, cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      result.setIndex(m.getIndex(i, j)*num, i, j);
    }
  }
  return result;
}
Matrix Matrix::operator=(const Matrix& m){
  this->rows = m.rows;
  this->cols = m.cols;
  this->matrix = new double*[rows]; //Allocate pointers each the size of a row
  for(int i = 0; i < rows; i++){
    matrix[i] = new double[cols]; //create a double for every number in each row
    for(int j = 0; j < cols; j++){
      matrix[i][j] = m.matrix[i][j];
    }
  }
  return *this;
}

Matrix Matrix::rref(){
  Matrix result = Matrix(*this);
  while(!result.is_rref()){
    int pivotx = 0;
    int pivoty = 0;
    int x1 = 0; //element to cancel out
    int y1 = 0;
    int y2 = 0; //row to use when doing arithmetic
    double coef = 0;

    //Basically, need to find the leading number in a row and then clear its column.
    //Finding the leading number:
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
        if(result.matrix[i][j] != 0){
          pivoty = i;
          pivotx = j;
          //Checking to see if that column has any other numbers in it
          for(int k = 0; k < rows; k++){
            if(result.matrix[k][j] != 0 && k!=i){
              //If it does, we'll need to make that the number to eliminate.
              y1 = k;
              x1 = j;
              coef = result.matrix[k][j];
              goto brk; //Don't tell anybody
            }
          }
          break; //If it doesn't have any other numbers in the column, don't check the rest of the row
        }
      }
    }
    brk:;

    //Find any other non-zero number in the same column
    for(int i = rows-1; i >= 0; i--){
      int j = x1;
      if(result.matrix[i][j] != 0 && i != y1){
        coef /= result.matrix[i][j];
        y2 = i;
        break;
      }
    }

    //Apply the coefficient to all elements in that row
    for(int j = 0; j < cols; j++){
      result.matrix[y1][j] = result.matrix[y1][j] - result.matrix[y2][j] * coef;
    }

    //If the pivot entry is not equal to 1, divide everything in its row by the pivot entry.
    if(result.matrix[pivoty][pivotx] != 1){
      for(int j = 0; j < cols; j++){
        if(j != pivoty){ //Can't divide the pivot entry yet, as its value can't change until after everything else
          result.matrix[pivoty][j] /= result.matrix[pivoty][pivotx];
        }
      }
    }
    result.matrix[pivoty][pivotx] = 1; //Finally apply the division to the pivot entry.
  }
  return result;
}

//Returns the cofactor matrix of a matrix
Matrix Matrix::cofactor(){
  Matrix result = Matrix(rows, cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      Matrix sub = this->submatrix(i, j);
      if(i + j & 1){ //Determine sign of cofactor entry
        result.matrix[i][j] = -sub.determinant();
      }else{
        result.matrix[i][j] = sub.determinant();
      }
    }
  }
  return result;
}
//Returns a matrix with a row and column removed
Matrix Matrix::submatrix(int r, int c){
  Matrix result = Matrix(cols-1, rows-1);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(i != r && j != c){ //Ignore row r and column c
        int y = i;
        int x = j;
        if(i > r) y--;
        if(j > c) x--;
        result.matrix[y][x] = this->matrix[i][j];
      }
    }
  }
  return result;
}
//Returns the transpose of a matrix
Matrix Matrix::transpose(){
  Matrix result = Matrix(cols, rows);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      result.matrix[j][i] = matrix[i][j];
    }
  }
  return result;
}

Matrix Matrix::inverse(){
  return Matrix(*this).cofactor().transpose() * (1.0/determinant());
}
double Matrix::determinant(){
  if(rows != cols){
    return 0;
  }
  if(rows == 1){
    return matrix[0][0];
  }else if(rows == 2){
    return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
  }

  double sum = 0;

  for(int r = 0; r < rows; r++){
    int c = 0;
    Matrix sub = submatrix(r, c);
    if(r+c & 1){
      sum -= matrix[r][c] * sub.determinant();
    }else{
      sum += matrix[r][c] * sub.determinant();
    }
  }
  return sum;
}
int Matrix::is_rref(){
  //First entry for a row must be 1
  //That column must contain only that one and zeroes
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(matrix[i][j] == 1){
        for(int k = 0; k < rows; k++){ //Check the rest of the column
          if(k != i && matrix[k][j] != 0) return 0;
        }
        break;
      }else if(j == cols-1){ //A row is allowed to be all 0's, check for that case
        for(int k = 0; k < cols; k++){
          if(matrix[i][k] != 0) return 0;
        }
      }
    }
  }
  return 1;
}
std::vector<double> Matrix::eigenvalues(){
  /* 1. Multiply entries on diagonal by -1
   * 2.
   *
   *
   *
   *
   */
   std::vector<double> ret;
   if(rows!=cols) return ret;
   if(rows == 2){
     double x = matrix[0][0];
     double y = matrix[0][1];
     double z = matrix[1][0];
     double w = matrix[1][1];
     ret = q_solver(1, x+w, x*w-z*y);
   }
   if(rows == 3){

   }
   return ret;

}
int Matrix::getRows() const{
  return this->rows;
}
int Matrix::getCols() const{
  return this->cols;
}
double Matrix::getIndex(int r, int c) const{
  if(r < rows && c < cols){
    return this->matrix[r][c];
  }
}
void Matrix::setIndex(double num, int r, int c){
  if(r < rows && c < cols){
    this->matrix[r][c] = num;
  }
}
void Matrix::printMatrix(){
  for(int i = 0; i < rows; i++){
    printf("|");
    for(int j = 0; j < cols; j++){
      double num = matrix[i][j];
      printf("%8.3f", num);
    }
    printf(" |\n");
  }
  printf("\n");
}
