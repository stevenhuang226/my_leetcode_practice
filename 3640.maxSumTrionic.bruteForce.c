#include "shdstd.h"

#define INF64 (INT64_MAX / 4)
#define NEG_INF64 -(INF64)

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int64_t maxSumTrionic(int *nums, int size)
{
	int64_t max_sum = NEG_INF64;

	for (int i = 0; i < size; ++i) {
		int peak, valley, end;

		int64_t sub_sum = 0;

		peak = i;
		while (peak < size - 1 && nums[peak] < nums[peak+1]) {
			sub_sum += nums[peak];
			++peak;
		}

		if (peak == i) {
			continue;
		} else {
			valley = peak;
		}

		while (valley < size - 1 && nums[valley] > nums[valley+1]) {
			sub_sum += nums[valley];
			++valley;
		}
		
		if (valley == peak) {
			continue;
		} else {
			end = valley;
		}

		while (end < size - 1 && nums[end] < nums[end+1]) {
			sub_sum += nums[end];
			max_sum = MAX(max_sum, sub_sum + nums[end+1]);
			++end;
		}
	}

	return max_sum;
}
