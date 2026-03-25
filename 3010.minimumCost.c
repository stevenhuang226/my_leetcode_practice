#include "shdstd.h"

int minimumCost(int *nums, int size)
{
	int cost = nums[0];

	int small = INT32_MAX;
	int mini = INT32_MAX;
	for (int i = 1; i < size; ++i) {
		int num = nums[i];
		if (num >= small) {
			continue;
		}
		if (num < mini) {
			small = mini;
			mini = num;
		} else {
			small = num;
		}
	}

	return cost + small + mini;
}
