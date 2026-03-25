#include "shdstd.h"

int comp(const void *a, const void *b)
{
	return *(int *)b - *(int *)a;
}

int64_t maxRunTime(int n, int *arr, int size)
{
	qsort(arr, size, sizeof(int), comp);

	int64_t sum = 0;

	int i;
	for (i = 0; i < size; ++i) {
		sum += arr[i];
	}

	for (i = 0; i < size; ++i) {
		if (arr[i] <= sum / n) {
			break;
		}

		sum -= arr[i];
		--n;
	}

	return sum / n;
}
