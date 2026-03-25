#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int **row_prefix;
int **sum_prefix;

int chk(const int r, const int c,
		const int start, const int end,
		const int limit)
{
	int k = start;
	while (k <= end) {
		int sum =
			sum_prefix[r+k][c+k] -
			sum_prefix[r][c+k] -
			sum_prefix[r+k][c] +
			sum_prefix[r][c];

		if (sum > limit) {
			break;
		}
		++k;
	}

	return k - 1;
}

int maxSideLength(int **mat, int size, int *col_size, int threshold)
{
	int rows = size;
	int cols = col_size[0];

	row_prefix = malloc(rows * sizeof(int *));
	int *row_prefix_flat = malloc(rows * (cols + 1) * sizeof(int));
	for (int i = 0; i < rows; ++i) {
		row_prefix[i] = row_prefix_flat + i * (cols + 1);
	}

	sum_prefix = malloc((rows + 1) * sizeof(int *));
	int *sum_prefix_flat = malloc((rows + 1) * (cols + 1) * sizeof(int));
	for (int i = 0; i <= rows; ++i) {
		sum_prefix[i] = sum_prefix_flat + i * (cols + 1);
	}

	for (int r = 0; r < rows; ++r) {
		row_prefix[r][0] = 0;
		for (int c = 0; c < cols; ++c) {
			row_prefix[r][c+1] = mat[r][c] + row_prefix[r][c];
		}
	}

	for (int c = 0; c <= cols; ++c) {
		sum_prefix[0][c] = 0;
		for (int r = 0; r < rows; ++r) {
			sum_prefix[r+1][c] = row_prefix[r][c] + sum_prefix[r][c];
		}
	}

	free(row_prefix);

	int max = 0;

	for (int r = 0; r < rows - max; ++r) {
		for (int c = 0; c < cols - max; ++c) {
			int end = MIN(rows - r, cols - c);
			int curr = chk(r, c, max + 1, end, threshold);
			max = MAX(max, curr);
		}
	}

	free(sum_prefix);

	return max;
}
