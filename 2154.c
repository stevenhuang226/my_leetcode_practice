#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define LIMIT_NUMS 1005

int findFinalValue(int *nums, int nums_size, int original)
{
	int8_t *mrk;
	mrk = calloc(LIMIT_NUMS, sizeof(int8_t));
	
	int i;
	for (i = 0; i < nums_size; ++i) {
		++mrk[nums[i]];
	}
	while (original < LIMIT_NUMS && mrk[original]) {
		original *= 2;
	}

	return original;
}
