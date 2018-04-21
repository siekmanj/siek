#include "./matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

double **create_matrix(int rows, int cols){
  double **matrix = (double **)malloc(rows*sizeof(double *)); //Allocate row number of pointers the size of
  for(int i = 0; i < rows; i++){
    matrix[i] = (double *)malloc(cols*sizeof(double)); //create a double for every column in each row
    for(int j = 0; j < cols; j++){
      matrix[i][j] = 0;
    }
  }
  return matrix;
}

double **matrix_from_static_array(int rows, int cols, double input[][cols]){ //Parameters passed backwards here for compilation reasons
  double **output = create_matrix(rows, cols);
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      output[i][j] = input[i][j];
    }
  }
  return output;
}

void rref(double **matrix, int rows, int cols){
  while(!is_rref(matrix, rows, cols) && cols == rows+1){
    int x1 = 0; //element to cancel out
    int y1 = 0;
    int y2 = 0; //row to use when doing arithmetic
    double coef = 0;

    //Find a non-zero, non-diagonal element
    for(int j = 0; j < cols-1; j++){
      for(int i = 0; i < rows; i++){
        if(matrix[i][j] != 0 && i != j){
          y1 = i;
          x1 = j;
          coef = matrix[i][j];
          goto brk; //Don't tell anybody
        }
      }
    }
    brk:;

    //Find a non-zero number in the same column
    for(int i = rows-1; i >= 0; i--){
      int j = x1;
      if(matrix[i][j] != 0 && i != y1){
        coef /= matrix[i][j];
        y2 = i;
        break;
      }
    }

    //Apply the coefficient to all elements in that row
    for(int j = 0; j < cols; j++){
      matrix[y1][j] = matrix[y1][j] - matrix[y2][j] * coef;
    }

    //If the diagonal entry is not equal to 1, divide everything in its row by the diagonal entry.
    if(matrix[y1][y1] != 1){
      for(int j = 0; j < cols; j++){
        if(j != y1){ //Don't divide the diagonal entry yet, as its value can't change until after everything else
          matrix[y1][j] /= matrix[y1][y1];
        }
      }
    }
    matrix[y1][y1] = 1;
  }
}

void determinant(double **matrix, int rows, int cols){
  assert(rows == cols);
  if(rows = 1){
    return matrix[0][0];
  }else if(rows == 2){
    return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
  }


}

int is_rref(double **matrix, int rows, int cols){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols-1; j++){
      if(matrix[i][j] != 0 && i != j){
        return 0;
      }
    }
  }
  return 1;
}

void free_matrix(double **matrix, int rows, int cols){
  for(int i = 0; i < rows; i++){
    free(matrix[i]);
  }
  free(matrix);
}

void print_matrix(double **matrix, int rows, int cols){
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
