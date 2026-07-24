#include "shdstd.h"

int uniqueXorTriplets(int *nums, int size)
{
	int exp_max = 1 << 12;
	int8_t *mark = malloc(exp_max * sizeof(int8_t));
	memset(mark, 0x00, exp_max * sizeof(int8_t));

	int *buffer = malloc(exp_max * sizeof(int));
	int bfr_ptr = 0;

	for (int i = 0; i < size; ++i) {
		for (int i2 = i; i2 < size; ++i2) {
			int new = nums[i] ^ nums[i2];
			if (mark[new])
				continue;

			mark[new] = true;
			buffer[bfr_ptr++] = new;
		}
	}

	memset(mark, 0x00, exp_max * sizeof(int8_t));
	int count = 0;

	for (int i = 0; i < bfr_ptr; ++i) {
		int x = buffer[i];
		for (int i2 = 0; i2 < size; ++i2) {
			int new = x ^ nums[i2];
			if (!mark[new]) {
				++count;
				mark[new] = true;
			}
		}
	}

	free(mark);
	free(buffer);

	return count;
}
