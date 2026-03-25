#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int32_t jump(int32_t *nums, int32_t size)
{
	int32_t range_end = 0;
	int32_t range = INT_MIN;
	int32_t jumps = 0;

	int i;
	for (i = 0; i < size; ++i) {
		range = MAX(range, i + nums[i]);
		if (i == range_end) {
			++jumps;
		}
		range_end = range;
	}

	return jumps;
}
