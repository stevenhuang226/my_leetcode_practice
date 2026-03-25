#include "shdstd.h"

static int32_t dx[2] = {0,1};
static int32_t dy[2] = {1,0};

int uniquePathsWithObstacles(int **obstacle, int size, int *p_col_size)
{
	int col_size = (*p_col_size);

	if (obstacle[0][0] == 1) {
		return 0;
	}

	int32_t **dp = malloc(size * sizeof(int32_t *));
	int32_t *dp_flat = calloc(1, size * col_size * sizeof(int32_t));

	int i;
	for (i = 0; i < size; ++i) {
		dp[i] = dp_flat + i * col_size;
	}
	dp[0][0] = 1;

	int i2,k;
	int dk = 2;
	for (i = 0; i < size; ++i) {
		for (i2 = 0; i2 < col_size; ++i2) {
			for (k = 0; k < dk; ++k) {
				int x = i + dx[k];
				int y = i2 + dy[k];

				if (x < size && y < col_size && (! obstacle[x][y])) {
					dp[x][y] += dp[i][i2];
				}
			}
		}
	}

	int32_t res = dp[size-1][col_size-1];
	free(dp_flat);
	free(dp);

	return res;
}
