#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define DEFAULT_TAIL_VAL -10005

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
int lengthOfLIS(int *nums, int nums_size)
{
	if (nums_size == 1) return 1;
	int *tail = malloc((nums_size+1) * sizeof(int));
	int i;
	for (i = 0; i <= nums_size; ++i) {
		tail[i] = DEFAULT_TAIL_VAL;
	}
	int tail_size = 0;
	for (i = 0; i < nums_size; ++i) {
		int target = nums[i];
		if (target > tail[tail_size]) {
			tail[++tail_size] = target;
		}
		int pos = lower_bound(tail, tail_size, target);
		tail[pos] = target;
	}
	free(tail);
	return tail_size;
}
