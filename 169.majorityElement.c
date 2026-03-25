#include "shdstd.h"

int majorityElement(int *nums, int size)
{
	int times = 0;
	int id;
	for (int i = 0; i < size; ++i) {
		int num = nums[i];

		if (times == 0) {
			id = num;
		}

		if (id != num) {
			--times;
		} else {
			++times;
		}
	}

	return id;
}
