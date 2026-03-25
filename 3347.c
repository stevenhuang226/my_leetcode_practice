#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>

int compare(const void *a, const void *b)
{
	return *(int *)a -  *(int *)b;
}
int maxFrequency(int *nums, int numsSize, int k, int numOperations)
{
	qsort(nums, numsSize, sizeof(nums[0]), compare);
	int max_num = nums[numsSize - 1];

	int i;

	int mid = nums[0];
	int mid_ptr = 0;
	int l_ptr = 0;
	int r_ptr = 1;


	int max = 0;

	for (;;) {
		int mid_count = 0;
		for (; nums[mid_ptr] < mid; ++mid_ptr);
		for (; mid_ptr < numsSize && nums[mid_ptr] == mid; ++mid_ptr) {
			++mid_count;
		}

		int l = (mid - k > 0) ? mid - k : 0;
		int r = mid + k;
		for (; nums[l_ptr] < l; ++l_ptr);
		for (; r_ptr < numsSize && nums[r_ptr] <= r; ) ++r_ptr;

		int sum = (r_ptr - l_ptr - mid_count < numOperations) ? r_ptr - l_ptr - mid_count : numOperations;

		sum += mid_count;

		if (sum > max) max = sum;

		if (mid_ptr >= numsSize) {
			break;
		}

		if (nums[l_ptr] == l) {
			mid++;
		} else {
			mid = (nums[l_ptr] + k < nums[mid_ptr]) ? nums[l_ptr] + k : nums[mid_ptr];
		}
	}

	return max;
}

int main()
{
	int arr[] = {14,140,143,114,98};
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	int k = 17;
	int num_operations = 5;

	int res = maxFrequency(arr, arr_size, k, num_operations);

	printf("%d\n", res);

	return 0;
}
