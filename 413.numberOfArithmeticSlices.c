#include "shdstd.h"

int numberOfArithmeticSlices(int *nums, int size)
{
	int *dp = calloc(size, sizeof(int));

	for (int i = 2; i < size; ++i) {
		if (nums[i] - nums[i-1] == nums[i-1] - nums[i-2]) {
			dp[i] = dp[i-1] + 1;
		} else {
			dp[i] = dp[i];
		}
	}

	int sum = 0;
	for (int i = 0; i < size; ++i) {
		sum += dp[i];
	}

	free(dp);
	return sum;
}
