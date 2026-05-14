#include "shdstd.h"

int cmp_i32(const void* l, const void* r)
{
	return *(int*)l - *(int*)r;
}

bool isGood(int* nums, int size)
{
	qsort(nums, size, sizeof(int), cmp_i32);

	++nums[size-1];

	int curr = 1;
	for (int i = 0; i < size; ++i) {
		if (nums[i] != curr) {
			return false;
		}
		++curr;
	}

	return true;
}
