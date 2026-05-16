#include "shdstd.h"

int findMin(int *nums, int size)
{
	int l = 0;
	int r = size-1;

	while (l < r) {
		int mid = (l + r) / 2;

		if (nums[mid] < nums[r]) {
			r = mid;
		} else if (nums[mid] > nums[r]) {
			l = mid + 1;
		} else {
			--r;
		}
	}

	return nums[l];
}
