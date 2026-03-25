#include "shdstd.h"

int cmp32(const void *a, const void *b)
{
	return *(int *)b - *(int *)a;
}

int hIndex(int *citations, int size)
{
	qsort(citations, size, sizeof(int), cmp32);

	int h;
	for (h = 0; h < size; ++h) {
		if (citations[h] <= h) {
			break;
		}
	}

	return h;
}
