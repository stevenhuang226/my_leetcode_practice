#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>

int compare(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int maxDistinctElements(int *nums, int numsSize, int k)
{
	qsort(nums, numsSize, sizeof(int), compare);
	int prev = INT_MIN;
	int i;

	int count = 0;

	for (i = 0; i < numsSize; i++) {
		int num = nums[i];

		if (num + k <= prev) {
			prev = num + k;
			continue;
		}

		count++;

		if (num - k < prev + 1) {
			prev++;
		} else {
			prev = num - k;
		}

		/*
		int cur_min = fmin(fmax(num - k, prev + 1), num + k);
		if (cur_min > prev) {
			prev = cur_min;
			count++;
		}
		*/
	}

	return count;
}
