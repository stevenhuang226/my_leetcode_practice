#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool *prefixesDivBy5(int *nums, int size, int *return_size)
{
	*return_size = size;
	bool *arr = malloc(*return_size * sizeof(bool));

	int i;
	int prefix[2] = {0};
	for (i = 0; i < size; ++i) {
		prefix[1] = prefix[0] * 2 + nums[i];

		if (prefix[1] % 5 == 0) {
			arr[i] = true;
		} else {
			arr[i] = false;
		}

		prefix[0] = prefix[1] % 5;
	}

	return arr;
}
