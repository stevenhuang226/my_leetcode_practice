#include "shdstd.h"

int cmp32(const void *l, const void *r)
{
	return *(int *)r - *(int *)l;
}

int64_t maxAlternatingSum(int *nums, int nums_size)
{
	for (int i = 0; i < nums_size; ++i) {
		nums[i] = abs(nums[i]);
	}

	qsort(nums, nums_size, sizeof(int), cmp32);

	int64_t sum = 0;
	int mid = (nums_size / 2) + (nums_size % 2);
	int i;
	for (i = 0; i < mid; ++i) {
		sum += (int64_t)nums[i] * nums[i];
	}
	for (; i < nums_size; ++i) {
		sum -= (int64_t)nums[i] * nums[i];
	}

	return sum;
}
