#include "shdstd.h"

int maxProduct(int *nums, int size)
{
	int max[2];
	max[0] = max[1] = 0;
	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		if (num > max[0]) {
			max[1] = max[0];
			max[0] = num;
		} else if (num > max[1]) {
			max[1] = num;
		}
	}

	return (max[0] - 1) * (max[1] - 1);
}
