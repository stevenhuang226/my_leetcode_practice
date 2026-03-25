#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int largestAltitude(int *gain, int size)
{
	int prefix = 0;
	int max = prefix;

	for (int i = 0; i < size; ++i) {
		prefix += gain[i];
		max = MAX(max, prefix);
	}

	return max;
}
