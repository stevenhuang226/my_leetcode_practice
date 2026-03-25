#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

bool isZeroArray(int *nums, int numsSize, int **queries, int queriesSize, int *queriesColSize)
{
	int *sub_array;
	sub_array = calloc(numsSize + 1, sizeof(int));
	for (int i = 0; i < queriesSize; ++i) {
		sub_array[queries[i][0]] += 1;
		sub_array[queries[i][1] + 1] -= 1;
	}

	int8_t is_zero = 1;
	int sub_value = 0;
	for (int i = 0; i < numsSize; ++i) {
		sub_value += sub_array[i];
		if (nums[i] > sub_value) {
			is_zero = 0;
			break;
		}
	}
	if (is_zero == 0) {
		return false;
	}

	return true;
}

int main()
{
	return 0;
}
