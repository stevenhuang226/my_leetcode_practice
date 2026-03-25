#include "shdstd.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

bool *kidsWithCandies(int *candies, int size, int extra_candies, int *p_return_size)
{
	int i;
	int src_max = 0;
	for (i = 0; i < size; ++i) {
		src_max = MAX(src_max, candies[i]);
	}

	bool *ret = malloc(size * sizeof(bool));
	(*p_return_size) = size;

	for (i = 0; i < size; ++i) {
		int src = candies[i];
		ret[i] = (src + extra_candies >= src_max);
	}

	return ret;
}
