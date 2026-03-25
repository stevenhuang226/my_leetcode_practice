#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int lower_bound(int *arr, int size, int target)
{
	int l = 0;
	int r = size;

	while (l < r) {
		int mid = (l + r) / 2;
		if (arr[mid] < target) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}

	return l;
}

int top_bound(int *arr, int size, int target)
{
	int l = 0;
	int r = size;

	while (l < r) {
		int mid = (l + r) / 2;
		if (arr[mid] <= target) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}

	return l - 1;
}

int *searchRange(int *nums, int nums_size, int target, int *return_size)
{
	*return_size = 2;
	int *ret = malloc(2 * sizeof(int));
	int8_t fail = 0;

	if (nums_size == 1) {
		if (nums[0] != target) {
			fail = 1;
		} else {
			ret[0] = 0;
			ret[1] = 0;
			return ret;
		}
	}


	int start = lower_bound(nums, nums_size, target);
	if (start >= nums_size || nums[start] != target) fail = 1;
	if (fail) {
		ret[0] = -1;
		ret[1] = -1;
		return ret;
	}
	int end = top_bound(nums, nums_size, target);
	ret[0] = start;
	ret[1] = end;
	return ret;
}
