#include "shdstd.h"

int *pivotArray(int *nums, int size, int pivot, int *ret_size)
{
	int *res = malloc(size * sizeof(int));
	int w = 0;
	int c = 0;
	int eq_count = 0;

	for (int i = 0; i < size; ++i) {
		int num = nums[i];

		if (num < pivot) {
			res[w++] = num;
		} else if (num == pivot) {
			++eq_count;
		} else {
			nums[c++] = num;
		}
	}

	for (int i = 0; i < eq_count; ++i) {
		res[w++] = pivot;
	}

	for (int i = 0; i < c; ++i) {
		res[w++] = nums[i];
	}

	*ret_size = size;
	return res;
}
