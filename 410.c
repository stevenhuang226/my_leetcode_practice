#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int splitArray(int *nums, int nums_size, int k)
{
	int64_t l = 0;
	int64_t r = 0;
	int i;
	for (i = 0; i < nums_size; ++i) {
		int n = nums[i];
		if (n > l) {
			l = n;
		}
		r += n;
	}
	++r;
	/*
	 * l => minimum sum possible
	 * r => maximum sum possible
	 * every group's sum will be in this range
	 */

	while (l < r) {
		int64_t mid = (l + r) / 2;
		int64_t curr_sum = 0;
		int64_t group_count = 1;
		/* 
		 * mid => maximum value for group's sum
		 * curr_sum => current group's sum
		 * group_count => how many group we have right now
		 */
		for (i = 0; i < nums_size; ++i) {
			int n = nums[i];
			curr_sum += n;
			if (curr_sum <= mid) {
				continue;
			}

			curr_sum = n;
			++group_count;
		}
		if (group_count > k) {
			l = mid + 1;
		} else {
			r = mid;
		}
		/*
		 * if group_count greater than what we want, increase maximum group's sum value aka l = mid + 1;
		 * else, we want maximum group value smaller, decrase maximum group's sum aka r = mid
		 */
	}

	return l;

	/*
	 * after binary search, l = r => minimum value for group sum, and number of group can also be k
	 */
}
