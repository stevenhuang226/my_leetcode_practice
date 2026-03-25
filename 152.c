#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

inline int64_t max(const int64_t a, const int64_t b)
{
	if (a > b) {
		return a;
	} else {
		return b;
	}
}

inline int64_t min(const int64_t a, const int64_t b)
{
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

int maxProduct(int* nums, int nums_size)
{
	int64_t curr_max = 1;
	int64_t curr_min = 1;

	int i;

	int maximum = INT_MIN;


	for (i = 0; i < nums_size; ++i) {
		int64_t n = nums[i];
		if (n < 0) {
			int64_t tmp = curr_max;
			curr_max = curr_min;
			curr_min = tmp;
		}

		curr_max = max(n, curr_max * n);
		curr_min = min(n, curr_min * n);

		maximum = max(curr_max, maximum);
	}
	maximum = max(curr_max, maximum);

	return maximum;
}
