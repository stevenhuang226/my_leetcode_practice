#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

int32_t countPartitions(int *nums, int size, int k)
{
	int32_t *dp = malloc(size * sizeof(int32_t));
	int32_t *prefix = calloc(1, (size + 2) * sizeof(int32_t));
	prefix[0] = 0;
	prefix[1] = 1;

	int32_t *max_queue = calloc(1, size * sizeof(int32_t));
	int32_t *min_queue = calloc(1, size * sizeof(int32_t));

	int max_head, max_low;
	int min_head, min_low;

	max_head = max_low = min_head = min_low = 0;

	int curr_left_limit = 0;
	int curr_right_limit = 0;

	while (curr_right_limit < size) {
		int curr_num = nums[curr_right_limit];
		while (max_head >= max_low && nums[max_queue[max_head]] <= curr_num) {
			--max_head;
		}
		max_queue[++max_head] = curr_right_limit;

		while (min_head >= min_low && nums[min_queue[min_head]] >= curr_num) {
			--min_head;
		}
		min_queue[++min_head] = curr_right_limit;

		while (nums[max_queue[max_low]] - nums[min_queue[min_low]] > k) {
			++curr_left_limit;
			if (max_queue[max_low] < curr_left_limit) {
				++max_low;
			}
			if (min_queue[min_low] < curr_left_limit) {
				++min_low;
			}
		}

		//printf("prefix[%d] (%d) - prefix[%d] (%d) ", curr_right_limit + 1, prefix[curr_right_limit + 1], curr_left_limit, prefix[curr_left_limit]);
		dp[curr_right_limit] = (prefix[curr_right_limit + 1] - prefix[curr_left_limit] + MOD) % MOD;
		//printf("dp[%d] = %d\n", curr_right_limit, dp[curr_right_limit + 1]);
		prefix[curr_right_limit + 2] = (dp[curr_right_limit] + prefix[curr_right_limit + 1]) % MOD;

		++curr_right_limit;
	}

	int32_t res = dp[size - 1];

	free(dp);
	free(prefix);
	free(max_queue);
	free(min_queue);

	return res;
}

int64_t main()
{
	int32_t nums[] = {9,4,1,3,7};
	int32_t k = 4;
	int32_t size = sizeof(nums) / sizeof(nums[0]);

	int32_t res = countPartitions(nums, size, k);

	printf("res:%d\n", res);

	return 0;
}
