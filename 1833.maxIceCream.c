#include "shdstd.h"

int cmp_i32(const void *l, const void *r)
{
	return *(int *)l - *(int *)r;
}

int maxIceCream(int *costs, int size, int coins)
{
	qsort(costs, size, sizeof(int), cmp_i32);

	int p = 0;
	int next = costs[p++];

	int count = 0;

	while (next <= coins) {
		coins -= next;
		++count;

		if (p >= size) {
			break;
		}

		next = costs[p++];
	}

	return count;
}
