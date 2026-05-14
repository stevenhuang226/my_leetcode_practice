#include "shdstd.h"



#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int minMoves(int *nums, int size, int limit)
{
	int *darr = calloc(1, (limit * 2 + 2) * sizeof(int));

	int range = size / 2;
	for (int i = 0; i < range; ++i) {
		int left = nums[i];
		int right = nums[size-1-i];

		int min = MIN(left, right);
		int max = MAX(left, right);

		darr[2] += 2;
		darr[min+1] -= 1;
		darr[min+max] -= 1;
		darr[min+max+1] += 1;
		darr[max+limit+1] += 1;
	}

	int start = 2;
	int end = limit*2;

	int best = INT32_MAX;
	int curr = 0;
	for (int i = start; i <= end; ++i) {
		curr += darr[i];
		best = MIN(best, curr);
	}

	free(darr);

	return best;
}
