#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int comp(const void *l, const void *r)
{
	return *(int *)r - *(int *)l;
}

int64_t maximumHappinessSum(int *happinese, int size, int k)
{
	qsort(happinese, size, sizeof(int), comp);

	int64_t sum = 0;
	for (int i = 0; i < k; ++i) {
		int64_t val = happinese[i] - i;
		if (val <= 0) {
			return sum;
		}
		sum += val;
	}

	return sum;
}
