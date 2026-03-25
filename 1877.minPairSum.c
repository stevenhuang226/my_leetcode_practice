#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int cmp32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int minPairSum(int *nums, int size)
{
	qsort(nums, size, sizeof(int), cmp32);

	int left = 0;
	int right = size - 1;

	int max = INT32_MIN;

	for (; left < right; ) {
		int pair_sum = nums[left++] + nums[right--];
		max = MAX(max, pair_sum);
	}

	return max;
}
