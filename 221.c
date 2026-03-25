#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

int maximalSquare(char **matrix, int size, int *p_col_size)
{
	int col_size = *p_col_size;

	int i, i2;

	int **dp = malloc((size + 1) * sizeof(int *));
	int *dp_flat = calloc(1, (size + 1) * (col_size + 1) * sizeof(int));
	for (i = 0; i <= size; ++i) {
		dp[i] = dp_flat + i * (col_size+1);
	}

	int max = 0;
	for (i = 1; i <= size; ++i) {
		for (i2 = 1; i2 <= col_size; ++i2) {
			if (matrix[i-1][i2-1] != '1') {
				continue;
			}
			int min;

			min = MIN(dp[i-1][i2], dp[i-1][i2-1]);
			min = MIN(min, dp[i][i2-1]);

			++min;

			dp[i][i2] = min;

			max = MAX(min, max);
		}
	}

	free(dp_flat);
	free(dp);

	return max * max;

}
