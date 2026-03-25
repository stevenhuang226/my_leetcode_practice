#include "shdstd.h"

#define INF64 (INT64_MAX / 4)
#define NEG_INF64 -(INF64)

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int maxSumTrionic(int *nums, int size)
{
	int start, end;
	
	int64_t max_sum = NEG_INF64;
	int64_t sub_sum = 0;

	while (end < size - 1 && nums[end] > nums[end+1]) ++end;
	start = end;
	while (end < size - 1 && nums[end] < nums[end+1]) {
		sub_sum += nums[end];
		++end;
	}

	while (end < size - 1) {
		while (end < size - 1 && nums[end] > nums[end+1]) {
			sub_sum += nums[end];
			++end;
		}
		if (end < size - 1 && nums[end] == nums[end+1]) {
			++end;

			start = end;
			sub_sum = nums[end];
			continue;
		}
		while (end < size - 1 && nums[end] < nums[end+1]) {
			sub_sum += nums[end];
			++end;

			max_sum = MAX(max_sum, sub_sum + nums[end]);
		}

		while (start < end && nums[start] < nums[start+1]) {
			sub_sum -= nums[start];
			++start;
		}
		while (start < end && nums[start] > nums[start+1]) {
			sub_sum -= nums[start];
			++start;
		}
	}

	return max_sum;
}
