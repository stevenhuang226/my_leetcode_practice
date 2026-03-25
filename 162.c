#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int findPeakElement(int *nums, int nums_size)
{
	int l = 0;
	int r = nums_size - 1;
	while (l < r) {
		int mid = (l + r) / 2;
		if (nums[mid] > nums[mid+1]) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}

	return l;
}
