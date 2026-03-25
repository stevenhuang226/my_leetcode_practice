#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

int rob(int *nums, int size)
{
	if (size < 2) {
		return nums[0];
	}
	if (size < 3) {
		return MAX(nums[0], nums[1]);
	}
	int dp[4] = {0};
	dp[1] = nums[0];
	dp[2] = nums[1];
	dp[3] = dp[1] + nums[2];

	int i;
	for (i = 3; i < size; ++i) {
		dp[0] = dp[1];
		dp[1] = dp[2];
		dp[2] = dp[3];
		dp[3] = MAX(dp[0], dp[1]) + nums[i];
	}

	int res = MAX(dp[3], dp[2]);
	return res;
}

int main()
{
	int nums[] = {1,2,3,1};
	int size = sizeof(nums) / sizeof(nums[0]);

	printf("%d\n", rob(nums, size));

	return 0;
}
