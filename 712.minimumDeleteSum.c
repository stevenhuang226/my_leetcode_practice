#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int minimumDeleteSum(char *left, char *right)
{
	int left_size = strlen(left);
	int right_size = strlen(right);

	int **dp = malloc((left_size+1) * sizeof(int *));
	int *dp_flat = malloc((left_size + 1) * (right_size + 1) * sizeof(int));
	for (int i = 0; i <= left_size; ++i) {
		dp[i] = dp_flat + i * (right_size + 1);
	}
	dp[0][0] = 0;
	for (int i = 0; i < left_size; ++i) {
		dp[i+1][0] = dp[i][0] + left[i];
	}
	for (int i2 = 0; i2 < right_size; ++i2) {
		dp[0][i2+1] = dp[0][i2] + right[i2];
	}

	for (int i = 0; i < left_size; ++i) {
		for (int i2 = 0; i2 < right_size; ++i2) {
			if (left[i] == right[i2]) {
				dp[i+1][i2+1] = dp[i][i2];
				continue;
			}
			dp[i+1][i2+1] = MIN(dp[i][i2+1] + left[i], dp[i+1][i2] + right[i2]);
		}
	}

	int res = dp[left_size][right_size];

	free(dp_flat);
	free(dp);

	return res;
}
