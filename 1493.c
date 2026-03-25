#include "shdstd.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int longestSubarray(int *nums, int size)
{
	int max = 0;

	int l = 0;
	int r = 0;

	while (r < size && nums[r] != 0) {
		++r;
	}
	if (r < size) {
		max = r;
	} else {
		max = r - 1;
	}
	++r;

	while (r < size) {
		while (nums[r] == 0 && nums[l++] != 0);
		max = MAX(max, r - l);
		++r;
	}

	return max;
}
