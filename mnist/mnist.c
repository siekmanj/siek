/* Interface for the mnist handwritten digits image dataset
 * Jonah Siekmann
 * 7/16/2018
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t extractInt32(uint8_t *ptr, size_t offset){
	uint32_t num = 0;
	for(int i = offset; i < offset+4; i++){
		num |= ptr[i] << (3-i)*8;
	}
	return num;
}
void printImage(uint8_t *ptr, size_t index, size_t rows, size_t cols){
	size_t size = rows*cols;
	int base = index*size + 16;
	for(int i = base; i < base+rows*cols; i++){
		if(i % cols == 0) printf("\n");
		if(ptr[i] < 5) printf(".");
		else if(ptr[i] < 100) printf(":");
		else if(ptr[i] < 175) printf("1");
		else if(ptr[i] < 255) printf("X");
	}
}
int main(){
	FILE *fp;
	int arr[1000];
	size_t bytes = 7840016;
	size_t size = 1;

	fp = fopen("t10k-images-idx3-ubyte", "rb");

	uint8_t *ptr = malloc(sizeof(char)*bytes);
	size_t s = fread(ptr, sizeof(uint8_t), bytes, fp);

	uint32_t magic_num = extractInt32(ptr, 0);
	int32_t	numImages = extractInt32(ptr, 4);
	int32_t numRows = extractInt32(ptr, 8);
	int32_t numCols = extractInt32(ptr, 12);

	printImage(ptr, 0, numRows, numCols);

	printf("\n");
}
