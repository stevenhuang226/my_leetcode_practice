#include "shdstd.h"

int uniqueXorTriplets(int *nums, int size)
{
	if (size <= 2) {
		return size;
	}

	int bit_len = 0;
	while (size) {
		++bit_len;
		size >>= 1;
	}

	return 1 << bit_len;
}
