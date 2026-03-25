#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define INF64 8000000000000000000

int64_t maxSubarraySum(int *nums, int size, int k)
{
	int64_t *prefix_sum = malloc((size + 1) * sizeof(int64_t));
	prefix_sum[0] = 0;
	int64_t *min_prefix_pre_mod = malloc(k * sizeof(int64_t));

	int i;
	for (i = 0; i < k; ++i) {
		min_prefix_pre_mod[i] = INF64;
	}

	int64_t max = INT64_MIN;
	for (i = 0; i < size; ++i) {
		int64_t curr_prefix = nums[i] + prefix_sum[i];
		prefix_sum[i+1] = curr_prefix;
	}
	for (i = 0; i <= size; ++i) {
		int64_t curr_prefix = prefix_sum[i];

		int64_t mod = i % k;
		max = MAX(max, curr_prefix - min_prefix_pre_mod[mod]);
		min_prefix_pre_mod[mod] = MIN(min_prefix_pre_mod[mod], curr_prefix);
	}

	free(prefix_sum);
	free(min_prefix_pre_mod);

	return max;
}
