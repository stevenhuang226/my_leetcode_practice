#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool canPartition(int *nums, int numsSize)
{
	int i,i2;
	int total_sum = 0;
	for (i = 0; i < numsSize; ++i) {
		total_sum += nums[i];
	}

	if (total_sum % 2 != 0) {
		return false;
	}
	int target = total_sum / 2;

	int8_t dp[target+1];
	dp[0] = 1;


	for (i = 0; i < numsSize; ++i) {
		int val = nums[i];
		for (i2 = target; i2 >= val; --i2) {
			dp[i2] |= dp[i2 - val];
		}
	}

	bool res = dp[target];

	return res;
}

int main()
{
	int nums[] = {1,2,5};
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = canPartition(nums, size);
	printf("%d\n", res);

	return 0;
}
