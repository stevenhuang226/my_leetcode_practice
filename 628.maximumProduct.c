#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int maximumProduct(int *nums, int size)
{
	int max[3];
	for (int i = 0; i < 3; ++i) {
		max[i] = INT32_MIN;
	}
	int min[2];
	for (int i = 0; i < 2; ++i) {
		min[0] = INT32_MAX;
	}

	for (int i = 0; i < size; ++i) {
		int num = nums[i];

		if (num > max[0]) {
			max[2] = max[1];
			max[1] = max[0];
			max[0] = num;
		} else if (num > max[1]) {
			max[2] = max[1];
			max[1] = num;
		} else if (num > max[2]) {
			max[2] = num;
		}

		if (num < min[0]) {
			min[1] = min[0];
			min[0] = num;
		} else if (num < min[1]) {
			min[1] = num;
		}
	}

	return MAX(max[0] * max[1] * max[2], min[0] * min[1] * max[0]);
}
