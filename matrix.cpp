#include "./matrix.h"
#include <stdio.h>



Matrix::Matrix(int rows, int cols){
  this->rows = rows;
  this->cols = cols;
  this->matrix = (double **)malloc(rows*sizeof(double *)); //Allocate row number of pointers the size of
  for(int i = 0; i < rows; i++){
    matrix[i] = (double *)malloc(cols*sizeof(double)); //create a double for every column in each row
    for(int j = 0; j < cols; j++){
      matrix[i][j] = 0;
    }
  }
}
Matrix::Matrix(const Matrix& m){
  this->rows = m.rows;
  this->cols = m.cols;
  this->matrix = (double **)malloc(rows*sizeof(double *)); //Allocate row number of pointers the size of
  for(int i = 0; i < rows; i++){
    matrix[i] = (double *)malloc(cols*sizeof(double)); //create a double for every column in each row
    for(int j = 0; j < cols; j++){
      matrix[i][j] = m.matrix[i][j];
    }
  }
}

Matrix::~Matrix(){
  for(int i = 0; i < rows; i++){
    free(matrix[i]);
  }
  free(matrix);
  free(&rows);
  free(&cols);
}
Matrix Matrix::operator+(const Matrix& m) const{
  if(this->cols != m.cols || this->rows != m.rows) throw "Incompatible matrix dimensions.";
  Matrix result = Matrix(this->rows, this->cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < rows; j++){
      result.matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];
    }
  }
  return result;
}
Matrix Matrix::operator-(const Matrix& m) const{
  if(this->cols != m.cols || this->rows != m.rows) throw "Incompatible matrix dimensions.";
  Matrix result = Matrix(this->rows, this->cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < rows; j++){
      result.matrix[i][j] = this->matrix[i][j] - m.matrix[i][j];
    }
  }
  return result;
}

Matrix Matrix::operator*(const Matrix& m) const{
  if(cols != m.rows) throw "Incompatible matrix dimensions.";
  Matrix result = Matrix(rows, m.cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < m.cols; j++){
      double sum = 0;
      for(int x = 0; x < m.rows; x++){
        sum += matrix[i][x] * m.matrix[x][j];
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
Matrix Matrix::rref(){
  Matrix result = Matrix(rows, cols);
  while(!is_rref() && cols == rows+1){
    int x1 = 0; //element to cancel out
    int y1 = 0;
    int y2 = 0; //row to use when doing arithmetic
    double coef = 0;

    //Find a non-zero, non-diagonal element
    for(int j = 0; j < cols-1; j++){
      for(int i = 0; i < rows; i++){
        if(result.matrix[i][j] != 0 && i != j){
          y1 = i;
          x1 = j;
          coef = result.matrix[i][j];
          goto brk; //Don't tell anybody
        }
      }
    }
    brk:;

    //Find a non-zero number in the same column
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

    //If the diagonal entry is not equal to 1, divide everything in its row by the diagonal entry.
    if(result.matrix[y1][y1] != 1){
      for(int j = 0; j < cols; j++){
        if(j != y1){ //Don't divide the diagonal entry yet, as its value can't change until after everything else
          result.matrix[y1][j] /= result.matrix[y1][y1];
        }
      }
    }
    result.matrix[y1][y1] = 1;
  }
  return result;
}

Matrix Matrix::cofactor(){
  Matrix result = Matrix(rows, cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      Matrix submatrix = Matrix(rows-1, cols-1);

      for(int r = 0; r < rows; r++){
        for(int c = 0 ; c < cols; c++){
          //Transcribe the rows*columns matrix into an (rows-1)*(columns-1) matrix, ignoring row i and column j
          if(r != i && c != j){
            int y = r;
            int x = c;
            if(r > i) y--;
            if(c > j) x--;
            submatrix.matrix[y][x] = matrix[r][c];
          }
        }
      }
      if(i + j & 1){
        result.matrix[i][j] = -submatrix.determinant();
      }else{
        result.matrix[i][j] = submatrix.determinant();
      }
    }
  }
  return result;
}
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
  Matrix result = Matrix(*this).cofactor().transpose() * (1.0/determinant());

  return result;
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
    Matrix submatrix = Matrix(rows-1, cols-1);

    //Transcribe the rows*columns matrix into an (rows-1)*(columns-1) matrix, ignoring row r and column c
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
        int x = j;
        int y = i;
        if(i != r && j != c){
          if(j > c) x = j-1;
          if(i > r) y = i-1;
          submatrix.matrix[x][y] = matrix[i][j];
        }
      }
    }
    double det = submatrix.determinant();

    if((r+1)+(c+1) & 1){
      sum -= matrix[r][c] * det;
    }else{
      sum += matrix[r][c] * det;
    }
  }
  return sum;
}
int Matrix::is_rref(){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols-1; j++){
      if(matrix[i][j] != 0 && i != j){
        return 0;
      }
    }
  }
  return 1;
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
    printf("| ");
    for(int j = 0; j < cols; j++){
      double num = matrix[i][j];
      printf("%10.4f ", num);
    }
    printf("|\n");
  }
  printf("\n");
}
/*



void transpose(double*** p, int rows, int cols){ //Needs a triple pointer because the array may need to be resized
  double** matrix = *p;
  if(rows == cols){
    for(int i = 0; i < rows; i++){
      for(int j = i; i < cols; i++){
        double temp = matrix[i][j];
        matrix[i][j] = matrix[j][i];
        matrix[j][i] = temp;
      }
    }
    return;
  }
  double** replacement = create_matrix(cols, rows);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      replacement[j][i] = matrix[i][j];
    }
  }
  *p = replacement;
}

void cofactor(double** matrix, int rows, int cols){
  double** temp = create_matrix(rows, cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      double** submatrix = create_matrix(rows-1, cols-1);

      for(int r = 0; r < rows; r++){
        for(int c = 0 ; c < cols; c++){
          //Transcribe the rows*columns matrix into an (rows-1)*(columns-1) matrix, ignoring row i and column j
          if(r != i && c != j){
            int y = r;
            int x = c;
            if(r > i) y--;
            if(c > j) x--;
            submatrix[y][x] = matrix[r][c];
          }
        }
      }
      if(i + j & 1){
        temp[i][j] = -determinant(submatrix, rows-1, cols-1);
      }else{
        temp[i][j] = determinant(submatrix, rows-1, cols-1);
      }
      free_matrix(submatrix, rows-1, cols-1);
    }
  }
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      matrix[i][j] = temp[i][j];
    }
  }
  free_matrix(temp, rows, cols);
}

void inverse(double** matrix, int rows, int cols){
  double** temp = copy_matrix(matrix, rows, cols);
  double*** p = &temp;
  cofactor(temp, rows, cols);
  transpose(p, rows, cols);

  double det = determinant(matrix, rows, cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      temp[i][j] /= det;
    }
  }
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      matrix[i][j] = temp[i][j];
    }
  }
  //free_matrix(temp, rows, cols);
}

double determinant(double** matrix, int rows, int cols){
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
    double** zoom = create_matrix(rows-1, cols-1);

    //Transcribe the rows*columns matrix into an (rows-1)*(columns-1) matrix, ignoring row r and column c
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < cols; j++){
        int x = j;
        int y = i;
        if(i != r && j != c){
          if(j > c) x = j-1;
          if(i > r) y = i-1;
          zoom[x][y] = matrix[i][j];
        }
      }
    }
    double det = determinant(zoom, rows-1, cols-1);
    free_matrix(zoom, rows-1, cols-1);

    if((r+1)+(c+1) & 1){
      sum -= matrix[r][c] * det;
    }else{
      sum += matrix[r][c] * det;
    }
  }
  return sum;
}

int is_rref(double** matrix, int rows, int cols){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols-1; j++){
      if(matrix[i][j] != 0 && i != j){
        return 0;
      }
    }
  }
  return 1;
}

void free_matrix(double** matrix, int rows, int cols){
  for(int i = 0; i < rows; i++){
    free(matrix[i]);
  }
  free(matrix);
}

void print_matrix(double** matrix, int rows, int cols){
  for(int i = 0; i < rows; i++){
    printf("| ");
    for(int j = 0; j < cols; j++){
      double num = matrix[i][j];
      printf("%10.4f ", num);
    }
    printf("|\n");
  }
  printf("\n");
}
*/
