#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int wiggleMaxLength(int *nums, int size)
{
	int up, down;
	up = down = 1;

	for (int i = 0; i < size - 1; ++i) {
		if (nums[i+1] > nums[i]) {
			up = down + 1;
		} else if (nums[i+1] < nums[i]) {
			down = up + 1;
		}
	}

	return MAX(up, down);
}
