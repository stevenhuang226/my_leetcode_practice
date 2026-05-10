#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int maximumJumps(int *nums, int size, int target)
{
	int *max_jump = malloc(size * sizeof(int));	// dp
	memset(max_jump, 0xff, size * sizeof(int));

	max_jump[0] = 0;
	for (int i = 0; i < size; ++i) {
		int curr = nums[i];
		for (int i2 = i-1; i2 >= 0; --i2) {
			if (max_jump[i2] < 0) continue;

			int prev = nums[i2];
			if (abs(curr-prev) <= target) {
				max_jump[i] = MAX(max_jump[i], max_jump[i2] + 1);
			}
			if (max_jump[i] >= i) {
				break;
			}
		}
	}

	int res = max_jump[size-1];
	free(max_jump);

	return res;
}
