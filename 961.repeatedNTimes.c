#include "shdstd.h"

#define MAX_N 5002

int repeatedNTimes(int *nums, int size)
{
	int8_t *mrk = calloc(MAX_N, sizeof(int8_t));

	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		
		if (mrk[num]) {
			return num;
		} else {
			mrk[num] = 1;
		}
	}

	return -1;
}
