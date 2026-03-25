#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int minimumOperations(int *nums, int size)
{
	int64_t count = 0;

	int i;
	for (i = 0; i < size; ++i) {
		count += ! (nums[i]%3 == 0);
	}

	return count;
}
