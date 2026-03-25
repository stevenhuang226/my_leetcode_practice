#include "shdstd.h"

int pivotIndex(int *nums, int size)
{
	int suffix = 0;
	for (int i = 0; i < size; ++i) {
		suffix += nums[i];
	}

	int prefix = 0;
	for (int i = 0; i < size; ++i) {
		prefix += nums[i];
		if (prefix == suffix) {
			return i;
		}
		suffix -= nums[i];
	}
	return -1;
}
