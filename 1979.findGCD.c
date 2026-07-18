#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int sgcd(int a, int b)
{
	while (b) {
		int t = a % b;
		a = b;
		b = t;
	}
	return a;
}

int findGCD(int *nums, int size)
{
	int min = INT32_MAX;
	int max = 0;
	for (int i = 0; i < size; ++i) {
		min = MIN(min, nums[i]);
		max = MAX(max, nums[i]);
	}

	return sgcd(min, max);
}
