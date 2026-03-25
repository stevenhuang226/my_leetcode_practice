#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define INF64 (INT64_MAX / 4)
int minSubArrayLen(int target, int *nums, int size)
{
	int left, right;
	left = right = 0;

	int64_t min_length = INF64;

	int64_t sum = 0;
	while (left < size) {
		while (right < size && sum < target) {
			sum += (int64_t)nums[right++];
		}

		if (sum >= target) {
			min_length = MIN(min_length, right - left);
		}

		sum -= nums[left++];
	}

	if (min_length == INF64) {
		return 0;
	}

	return min_length;
}
