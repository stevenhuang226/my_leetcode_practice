#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define INF64 8000000000000000000

int64_t maxSubarraySum(int *nums, int size, int k)
{
	int64_t *min_prefix_pre_mod = malloc(k * sizeof(int64_t));

	int i;
	for (i = 0; i < k - 1; ++i) {
		min_prefix_pre_mod[i] = INF64;
	}
	min_prefix_pre_mod[k - 1] = 0;

	int64_t max = INT64_MIN;
	int64_t curr_prefix = 0;
	for (i = 0; i < size; ++i) {
		curr_prefix += nums[i];

		int mod = i % k;
		max = MAX(max, curr_prefix - min_prefix_pre_mod[mod]);
		min_prefix_pre_mod[mod] = MIN(min_prefix_pre_mod[mod], curr_prefix);
	}

	free(min_prefix_pre_mod);

	return max;
}
