#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint64_t count;

int64_t glower;
int64_t gupper;

int64_t *tmp_arr;

void merge(int64_t *arr, int left, int right)
{
	if (right - left <= 1) {
		return;
	}

	int mid = (left + right) / 2;

	merge(arr, left, mid);
	merge(arr, mid, right);

	int lptr, rlow, rup;
	rlow = rup = mid;

	for (lptr = left; lptr < mid; ++lptr) {
		int64_t min = arr[lptr] + glower;
		int64_t max = arr[lptr] + gupper;

		while (rlow < right && arr[rlow] < min) {
			++rlow;
		}

		while (rup < right && arr[rup] <= max) {
			++rup;
		}

		count += rup - rlow;
	}

	int ptr = left;
	int pl = left, pr = mid;
	while (pl < mid && pr < right) {
		if (arr[pl] < arr[pr]) {
			tmp_arr[ptr++] = arr[pl++];
		} else {
			tmp_arr[ptr++] = arr[pr++];
		}
	}
	while (pl < mid) {
		tmp_arr[ptr++] = arr[pl++];
	}
	while (pr < right) {
		tmp_arr[ptr++] = arr[pr++];
	}

	for (ptr = left; ptr < right; ++ptr) {
		arr[ptr] = tmp_arr[ptr];
	}

	return;
}

int countRangeSum(int *nums, int numsSize, int lower, int upper)
{
	count = 0;
	glower = (int64_t)lower;
	gupper = (int64_t)upper;
	int i;
	int size = numsSize + 1;
	int64_t *prefix_arr = malloc(size * sizeof(int64_t));
	prefix_arr[0] = 0;
	tmp_arr = malloc(size * sizeof(int64_t));

	for (i = 0; i < numsSize; ++i) {
		prefix_arr[i+1] = prefix_arr[i] + nums[i];
	}

	merge(prefix_arr, 0, size);

	free(prefix_arr);
	free(tmp_arr);

	return count;
}

int main()
{
	int nums[] = {-2, 5, -1};
	int lower = -2;
	int upper = 2;

	int size = sizeof(nums) / sizeof(nums[0]);

	int res = countRangeSum(nums, size, lower, upper);

	printf("%d\n", res);

	return 0;
}
