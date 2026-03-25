#include "shdstd.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int longestOnes(int *nums, int size, int k)
{
	int zero_count = 0;
	int l = 0;
	int r = 0;
	int max_length;

	while (r < size) {
		zero_count += nums[r++] == 0;

		while (l < size && zero_count > k) {
			zero_count -= nums[l++] == 0;
		}

		max_length = MAX(max_length, r - l);
	}

	return max_length;
}
