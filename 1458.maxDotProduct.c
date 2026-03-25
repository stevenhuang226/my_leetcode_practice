#include "shdstd.h"

#define INF8 (INT8_MAX / 4)
#define INF16 (INT16_MAX / 4)
#define INF32 (INT32_MAX / 4)
#define INF64 (INT64_MAX / 4)
#define NEG_INF8 -(INF8)
#define NEG_INF16 -(INF16)
#define NEG_INF32 -(INF32)
#define NEG_INF64 -(INF64)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int maxDotProduct(int *left, int left_size, int *right, int right_size)
{
	int **dp = malloc((left_size+1) * sizeof(int *));
	int *dp_flat = malloc((left_size+1) * (right_size+1) * sizeof(int));

	for (int i = 0; i <= left_size; ++i) {
		dp[i] = dp_flat + i * (right_size+1);
	}
	dp[0][0] = NEG_INF32;

	for (int i = 0; i < left_size; ++i) {
		for (int i2 = 0; i2 < right_size; ++i2) {
			int max = left[i] * right[i2];

			max = MAX(max, max + dp[i][i2]);
			max = MAX(max, dp[i][i2]);
			max = MAX(max, dp[i+1][i2]);
			max = MAX(max, dp[i][i2+1]);

			dp[i+1][i2+1] = max;
		}
	}

	int res = dp[left_size][right_size];
	
	free(dp_flat);
	free(dp);

	return res;
}
