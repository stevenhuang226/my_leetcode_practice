#include "shdstd.h"

int removeDuplicates(int *nums, int size)
{
	if (size <= 2) {
		return size;
	}

	int wptr = 2;
	int rptr = 2;

	while (rptr < size) {
		if (nums[rptr] != nums[wptr-2]) {
			nums[wptr++] = nums[rptr];
		}
		++rptr;
	}

	return wptr;
}
