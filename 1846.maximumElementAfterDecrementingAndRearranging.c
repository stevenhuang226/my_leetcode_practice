#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int cmp_i32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int maximumElementAfterDecrementingAndRearranging(int *arr, int size)
{
	qsort(arr, size, sizeof(int), cmp_i32);

	arr[0] = 1;
	for (int i = 1; i < size; ++i) {
		arr[i] = MIN(arr[i], arr[i-1] + 1);
	}

	return arr[size-1];
}
