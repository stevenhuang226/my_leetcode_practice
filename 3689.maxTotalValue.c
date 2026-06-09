#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int64_t maxTotalValue(int *nums, int size, int k)
{
	int64_t max, min;

	max = 0;
	min = INT64_MAX;

	for (int i = 0; i < size; ++i) {
		int64_t num = nums[i];

		max = MAX(max, num);
		min = MIN(min, num);
	}

	return (max - min) * (int64_t)k;
}
