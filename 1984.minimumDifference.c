#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int cmp32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int minimumDifference(int *nums, int size, int k)
{
	qsort(nums, size, sizeof(int), cmp32);

	int left = 0;

	int min_diff = INT32_MAX;

	for (; left + k - 1 < size; ++left) {
		min_diff = MIN(min_diff, nums[left + k - 1] - nums[left]);
	}

	return min_diff;
}
