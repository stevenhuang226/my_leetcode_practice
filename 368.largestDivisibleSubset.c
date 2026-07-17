#include "shdstd.h"

int cmp_i32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int *largestDivisibleSubset(int *nums, int size, int *ret_size)
{
	qsort(nums, size, sizeof(int), cmp_i32);

	int *dp = malloc(size * sizeof(int));
	int *parent = malloc(size * sizeof(int));

	for (int i = 0; i < size; ++i) {
		dp[i] = 1;
		parent[i] = -1;

		int curr = nums[i];
		for (int i2 = 0; i2 < i; ++i2) {
			if (curr % nums[i2] || dp[i2] < dp[i])
				continue;

			dp[i] = dp[i2] + 1;
			parent[i] = i2;
		}
	}

	int count = 0;
	int id = -1;
	for (int i = 0; i < size; ++i) {
		if (dp[i] > count) {
			id = i;
			count = dp[i];
		}
	}

	int *res = malloc(count * sizeof(int));
	int p = 0;

	do {
		res[p++] = nums[id];
	} while ((id = parent[id]) >= 0);

	*ret_size = p;
	return res;
}
