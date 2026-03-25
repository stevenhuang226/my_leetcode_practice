#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

bool increasingTriplet(int *nums, int size)
{
	int most_min = INT_MAX;
	int min = INT_MAX;

	int i;
	for (i = 0; i < size; ++i) {
		int num = nums[i];
		most_min = MIN(most_min, num);
		if (most_min == num) {
			continue;
		}
		min = MIN(min, num);
		if (min == num) {
			continue;
		}
		return true;
	}

	return false;
}
