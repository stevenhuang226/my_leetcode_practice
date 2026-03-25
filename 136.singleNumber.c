#include "shdstd.h"

int singleNumber(int *nums, int size)
{
	int num = 0x00;
	for (int i = 0; i < size; ++i) {
		num = num ^ nums[i];
	}

	return num;
}
