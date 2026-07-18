#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int combinationSum4(int *nums, int nums_size, int target)
{
	int64_t *ways = calloc((target+1), sizeof(int64_t));

	ways[0] = 1;
	for (int i = 0; i <= target; ++i) {
		for (int i2 = 0; i2 < nums_size; ++i2) {
			int sz = nums[i2];
			if (i + sz > target)
				continue;
			ways[i+sz] += ways[i];
			ways[i+sz] = MIN(ways[i+sz], INT32_MAX);
		}
	}

	int res = ways[target];
	free(ways);

	return res;
}
