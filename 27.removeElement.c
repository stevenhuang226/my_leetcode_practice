#include "shdstd.h"

int removeElement(int *nums, int size, int val)
{
	int readptr = 0;
	int writeptr = 0;

	int count = 0;

	while (readptr < size) {
		int num = nums[readptr++];
		if (num == val) {
			continue;
		}
		++count;
		nums[writeptr++] = num;
	}

	return count;
}
