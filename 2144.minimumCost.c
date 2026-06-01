#include "shdstd.h"

static inline int cmp_i32(const void *l, const void *r)
{
	return *(int *)r - *(int *)l;
}

int minimumCost(int *cost, int size)
{
	qsort(cost, size, sizeof(int), cmp_i32);

	int sum = 0;
	int i;
	for (i = 0; i+1 < size; i += 3) {
		sum += cost[i] + cost[i+1];
	}
	if (i < size) {
		sum += cost[i];
	}

	return sum;
}
