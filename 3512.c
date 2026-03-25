#include "shdstd.h"

int minOperations(int *nums, int size, int k)
{
	int mod = 0;
	int i;
	for (i = 0; i < size; ++i) {
		int num = nums[i];
		mod = (mod + num) % k;
	}

	return mod;
}
