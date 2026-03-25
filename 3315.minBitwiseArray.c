#include "shdstd.h"

int *minBitwiseArray(int *nums, int size, int *ret_size)
{
	*ret_size = size;
	int *ret = malloc((*ret_size) * sizeof(int));

	for (int i = 0; i < size; ++i) {
		int num = nums[i];

		/* thing that not fit in rule (aka % 2 == 0) */
		if (! (num & 0x01)) {
			ret[i] = -1;
			continue;
		}

		int mask = 0x01;
		int tmp = num;
		while (tmp & 0x01) {
			mask <<= 1;
			tmp >>= 1;
		}
		mask >>= 1;

		ret[i] = num ^ mask;
	}

	return ret;
}
