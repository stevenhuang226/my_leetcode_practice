#include "shdstd.h"

int *leftRightDifference(int *nums, int size, int *ret_size)
{
	int suffix = 0;
	for (int i = size-1; i > 0; --i) {
		suffix += nums[i];
	}

	int *res = malloc(size * sizeof(int));
	*ret_size = size;

	int prefix = 0;
	for (int i = 0; i < size; ++i) {
		res[i] = abs(prefix - suffix);

		prefix += nums[i];
		if (i+1 < size) {
			suffix -= nums[i+1];
		}
	}

	return res;
}
