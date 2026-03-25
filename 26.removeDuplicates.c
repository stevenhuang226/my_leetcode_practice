#include "shdstd.h"

int removeDuplicates(int *nums, int size)
{
	int wptr = 1;
	int rptr = 1;

	while (rptr < size) {
		if (nums[rptr] != nums[rptr - 1]) {
			nums[wptr++] = nums[rptr];
		}
		++rptr;
	}

	return wptr;
}
