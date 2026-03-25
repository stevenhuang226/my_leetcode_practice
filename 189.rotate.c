#include "shdstd.h"

void reverse(int *arr, int size)
{
	for (int i = 0; i * 2 < size; ++i) {
		int tmp = arr[i];
		arr[i] = arr[size - i - 1];
		arr[size - i - 1] = tmp;
	}
}

void rotate(int *nums, int size, int k)
{
	if (k == 0 || size == 1) {
		return;
	}

	k = k % size;

	reverse(nums, size);
	reverse(nums, k);
	reverse(nums + k, size - k);
}
