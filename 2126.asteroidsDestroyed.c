#include "shdstd.h"

int cmpi32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

bool asteroidsDestroyed(int mass, int *asterids, int size)
{
	qsort(asterids, size, sizeof(int), cmpi32);

	int64_t m = (int64_t)mass;
	for (int i = 0; i < size; ++i) {
		int curr = asterids[i];
		if (m < curr) {
			return false;
		}

		m += (int64_t)curr;
	}

	return true;
}
