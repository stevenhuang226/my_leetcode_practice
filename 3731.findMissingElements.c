#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int *findMissingElements(int *nums, int size, int *ret_size)
{
	int8_t exist[108] = {false};

	int min, max;
	min = INT32_MAX;
	max = INT32_MIN;

	for (int i = 0; i < size; ++i) {
		min = MIN(min, nums[i]);
		max = MAX(max, nums[i]);

		exist[nums[i]] = true;
	}

	int range = max - min + 1;
	int *res = malloc(range * sizeof(int));

	int p = 0;
	for (int i = min; i <= max; ++i) {
		if (!exist[i]) {
			res[p++] = i;
		}
	}

	*ret_size = p;
	return res;
}
