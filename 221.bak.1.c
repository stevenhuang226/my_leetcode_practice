#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

#define INF 10000000

static int dx[] = {-1,-1,0};
static int dy[] = {0, -1, -1};

int maximalSquare(char **matrix, int size, int *p_col_size)
{
	int col_size = *p_col_size;

	if (size == 1) {
		return matrix[0][0] - '0';
	}

	int i, i2, k;
	int **dp = malloc(size * sizeof(int *));
	int *dp_flat = calloc(1, size * col_size * sizeof(int));
	for (i = 0; i < size; ++i) {
		dp[i] = dp_flat + i * col_size;
	}


	int max = INT_MIN;

	for (i = 0; i < size; ++i) {
		for (i2 = 0; i2 < col_size; ++i2) {
			if (matrix[i][i2] == '0') {
				continue;
			}
			int min = INF;
			for (k = 0; k < 3; ++k) {
				int x = i + dx[k];
				int y = i2 + dy[k];
				if (x < 0 ||
					x >= size ||
					y < 0 ||
					y >= col_size) {
					continue;
				}
				min = MIN(min, dp[x][y]);
			}
			if (min == INF) {
				continue;
			}
			max = MAX(max, min);
			dp[i][i2] = min + 1;
		}
	}
	free(dp_flat);
	free(dp);
	return max * max;
}
