#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
static inline int smax(const int a, const int b)
{
	return MAX(a, b);
}
static inline int smin(const int a, const int b)
{
	return MIN(a, b);
}
int minimumDeletions(int *nums, int nums_size)
{
	int max_id = 0;
	int min_id = 0;

	for (int i = 0; i < nums_size; ++i) {
		if (nums[i] > nums[max_id]) {
			max_id = i;
		} else if (nums[i] < nums[min_id]) {
			min_id = i;
		}
	}

	int left = smin(max_id, min_id) + 1;
	int right = smax(max_id, min_id) + 1;
	++nums_size;

	return smin(
		smin(right, nums_size - left),
		left + nums_size - right);
}
