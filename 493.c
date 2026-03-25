#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t count;

int *tmp;

void merge(int *arr, int left, int right)
{
	if (right - left <= 1) return;

	int mid = (left + right) / 2;

	merge(arr, left, mid);
	merge(arr, mid, right);

	int l, r;

	for (l = left, r = mid; r < right && l < mid;) {
		int64_t rnum = arr[r];
		rnum *= 2;
		int64_t lnum = arr[l];
		if (lnum > rnum) {
			count += mid - l;
			++r;
		} else {
			++l;
		}
	}

	int tptr = left;
	for (l = left, r = mid; l < mid && r < right; ) {
		if (arr[l] < arr[r]) {
			tmp[tptr++] = arr[l++];
		} else {
			tmp[tptr++] = arr[r++];
		}
	}

	while (l < mid) {
		tmp[tptr++] = arr[l++];
	}
	while (r < right) {
		tmp[tptr++] = arr[r++];
	}

	for (tptr = left; tptr < right; ++tptr) {
		arr[tptr] = tmp[tptr];
	}

	return;
}

int reversePairs(int *nums, int numsSize)
{
	count = 0;
	tmp = malloc(numsSize * sizeof(int));
	merge(nums, 0, numsSize);
	free(tmp);
	return count;
}

int main()
{
	int nums[] = {1,3,2,3,1};
	int size = sizeof(nums) / sizeof(nums[0]);
	int res = reversePairs(nums, size);
	printf("%d\n", res);

	return 0;
}
