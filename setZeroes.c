#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

void setZeroes(int **matrix, int matrixSize, int *matrixColSize)
{
	int *M_array;
	M_array = calloc(matrixSize, sizeof(int));
	int *N_array;
	N_array = calloc(*matrixColSize, sizeof(int));
	for (int i = 0; i < matrixSize; i++) {
		for (int ii = 0; ii < *matrixColSize; ii++) {
			if (matrix[i][ii] == 0) {
				M_array[i] = 1;
				N_array[ii] = 1;
			}
		}
	}
	for (int i = 0; i < matrixSize; i++) {
		if (M_array[i] == 0) {
			continue;
		}
		
		for (int ii = 0; ii < *matrixColSize; ii++) {
			matrix[i][ii] = 0;
		}
	}

	for (int i = 0; i < *matrixColSize; i++) {
		if (N_array[i] == 0) {
			continue;
		}

		for (int ii = 0; ii < matrixSize; ii++) {
			matrix[ii][i] = 0;
		}
	}
	free(M_array);
	free(N_array);
	return;
}


