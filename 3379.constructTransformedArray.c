#include "shdstd.h"

int *constructTransformedArray(int *nums, int size, int *ret_size)
{
	int *ret = malloc(size * sizeof(int));

	for (int i = 0; i < size; ++i) {
		int num = nums[i];

		if (num > 0) {
			int trg = (i + num) % size;
			ret[i] = nums[trg];
		} else if (num < 0) {
			int trg = ((i + size) - (abs(num) % size)) % size;
			ret[i] = nums[trg];
		} else if (num == 0) {
			ret[i] = num;
		}
	}

	*ret_size = size;
	return ret;
}
