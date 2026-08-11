#include "shdstd.h"

int missingInteger(int *nums, int size)
{
	int8_t exist[58] = {false};
	for (int i = 0; i < size; ++i) {
		exist[nums[i]] = true;
	}

	int sum = nums[0];
	int i = 0;
	while (i < size-1 && nums[i+1] == nums[i] + 1) {
		sum += nums[++i];
	}

	while (sum <= 50 && exist[sum]) {
		++sum;
	}

	return sum;
}
