#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

int main()
{
}

int minimumTotal(int **triangle, int triangleSize, int *triangleColSize)
{
	if (triangleSize == 1) {
		return triangle[0][0];
	}

	int32_t *last_line;
	int32_t *buffer;
	int32_t *ptr_bfr;

	last_line = malloc(200 * sizeof(int32_t));
	buffer = malloc(200 * sizeof(int32_t));

	last_line[0] = triangle[0][0];

	for (int i = 1; i < triangleSize; i++) {
		for (int ii = 0; ii < i+1; ii++) {
			if (ii == 0) {
				buffer[ii] = last_line[0] + triangle[i][ii];
				continue;
			}
			if (ii == i) {
				buffer[ii] = last_line[i-1] + triangle[i][ii];
				continue;
			}

			if (last_line[ii-1] < last_line[ii]) {
				buffer[ii] = last_line[ii-1] + triangle[i][ii];
			}
			else {
				buffer[ii] = last_line[ii] + triangle[i][ii];
			}
		}

		ptr_bfr = last_line;
		last_line = buffer;
		buffer = ptr_bfr;
	}

	free(buffer);

	int32_t min = INT_MAX;
	for (int i = 0; i < triangleSize; i++) {
		if (last_line[i] < min) {
			min = last_line[i];
		}
	}

	free(last_line);
	return min;
}
