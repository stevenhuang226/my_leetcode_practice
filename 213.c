#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

int rob(int *nums, int size)
{
	if (size <= 1) {
		return nums[0];
	}
	if (size <= 2) {
		return MAX(nums[0], nums[1]);
	}
	int *dp = calloc(size + 1, sizeof(int));
	int i, res;

	dp[0] = nums[0];
	dp[1] = MAX(nums[1], nums[0]);
	for (i = 2; i < size - 1; ++i) {
		dp[i] = MAX(dp[i-1], dp[i-2] + nums[i]);
	}
	res = dp[size-2];

	memset(dp, 0x00, sizeof(dp));
	dp[0] = 0;
	dp[1] = nums[1];
	for (i = 2; i < size; ++i) {
		dp[i] = MAX(dp[i-1], dp[i-2] + nums[i]);
	}
	res = MAX(res, dp[size-1]);
	free(dp);
	return res;
}

int main()
{
	int nums[] = {1,2,3,1};
	int size = sizeof(nums) / sizeof(nums[0]);

	printf("%d\n", rob(nums, size));

	return 0;
}
