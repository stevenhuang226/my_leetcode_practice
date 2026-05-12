#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int *maxValue(int *nums, int size, int *ret_size)
{
	int *res = malloc(size * sizeof(int));
	*ret_size = size;

	int *prefix_max = malloc((size+1) * sizeof(int));
	prefix_max[0] = 0;
	for (int i = 0; i < size; ++i) {
		prefix_max[i+1] = MAX(prefix_max[i], nums[i]);
	}

	int suffix_min = nums[size-1];
	res[size-1] = prefix_max[size];
	for (int i = size-2; i >= 0; --i) {
		if (prefix_max[i+1] > suffix_min) {
			res[i] = res[i+1];
		} else {
			res[i] = prefix_max[i+1];
		}

		suffix_min = MIN(suffix_min, nums[i]);
	}

	free(prefix_max);
	return res;
}
