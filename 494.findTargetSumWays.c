#include "shdstd.h"

#define MAXN 2016
int findTargetSumWays(int *nums, int size, int target)
{
	int *curr = calloc(MAXN, sizeof(int));
	int *next = calloc(MAXN, sizeof(int));

	int offset = 1e3 + 8;

	curr[offset] = 1;

	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		for (int i2 = 0; i2 < MAXN; ++i2) {
			if (curr[i2]) {
				next[i2 + num] += curr[i2];
				next[i2 - num] += curr[i2];
			}
		}

		int *tmp = curr;
		curr = next;
		next = tmp;
		memset(next, 0x00, MAXN * sizeof(int));
	}

	int res = curr[target+offset];

	free(curr);
	free(next);

	return res;
}
