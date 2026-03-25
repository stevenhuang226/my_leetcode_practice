#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int cols;
int rows;

int maximalRectangle(char **matrix, int size, int *col_size)
{
	rows = size;
	cols = col_size[0];

	int *height = calloc(cols, sizeof(int));

	int *stack = malloc(cols * sizeof(int));
	int top = -1;

	int max = 0;

	for (int i = 0; i < rows; ++i) {
		for (int i2 = 0; i2 < cols; ++i2) {
			if (matrix[i][i2] == '1') {
				++height[i2];
			} else {
				height[i2] = 0;
			}
		}

		for (int i2 = 0; i2 < cols; ++i2) {
			while (top >= 0 && height[i2] < height[stack[top]]) {
				int h = height[stack[top--]];
				int w;
				if (top < 0) {
					w = i2;
				} else {
					w = i2 - stack[top] - 1;
				}
				max = MAX(max, w * h);
			}
			stack[++top] = i2;
		}
		while (top >= 0) {
			int h = height[stack[top--]];
			int w;
			if (top < 0) {
				w = cols;
			} else {
				w = cols - stack[top] - 1;
			}
			max = MAX(max, w * h);
		}
	}

	free(height);
	free(stack);

	return max;
}
