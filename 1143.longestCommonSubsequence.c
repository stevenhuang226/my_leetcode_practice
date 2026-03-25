#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int longestCommonSubsequence(char *left, char *right)
{
	int size_left = strlen(left);
	int size_right = strlen(right);

	if (size_left == 0 || size_right == 0) {
		return 0;
	}

	int **dp = malloc((size_left + 1) * sizeof(int *));
	int *dp_flat = calloc(1, (size_left + 1) * (size_right + 1) * sizeof(int));
	for (int i = 0; i < size_left + 1; ++i) {
		dp[i] = dp_flat + i * (size_right + 1);
	}

	for (int l = 0; l < size_left; ++l) {
		for (int r = 0; r < size_right; ++r) {
			if (left[l] == right[r]) {
				dp[l+1][r+1] = dp[l][r] + 1;
			} else {
				dp[l+1][r+1] = MAX(dp[l][r+1], dp[l+1][r]);
			}
		}
	}

	int res = dp[size_left][size_right];
	free(dp_flat);
	free(dp);
	return res;
}
