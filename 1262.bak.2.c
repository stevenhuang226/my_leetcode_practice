#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MOD 3

int maxSumDivThree(int *nums, int size)
{
	int arr_dp[MOD] = {0,-1,-1};
	int arr_curr[MOD] = {0,-1,-1};
	int *dp = arr_dp;
	int *curr = arr_curr;

	int i,i2;
	for (i = 0; i < size; ++i) {
		int num = nums[i];
		int r = num % MOD;

		for (i2 = 0; i2 < MOD; ++i2) {
			int from = (i2 - r + MOD) % MOD;
			if (dp[from] < 0) continue;
			curr[i2] = dp[from] + num;
			if (curr[i2] < dp[i2]) {
				curr[i2] = dp[i2];
			}
		}
		printf("%d, %d, %d\n%d, %d, %d\n", dp[0], dp[1], dp[2], curr[0], curr[1], curr[2]);
		memcpy(dp, curr, sizeof(int) * MOD);
	}

	return dp[0];
}
int main()
{
	int nums[] = {2,6,2,2,7};
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = maxSumDivThree(nums, size);

	printf("%d\n", res);

	return 0;
}
