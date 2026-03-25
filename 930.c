#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int numSubarraysWithSum(int *nums, int size, int target)
{
	int count = 0;
	int prefix = 0;

	int *freq = calloc(size+1, sizeof(int));
	freq[0] = 1;
	/*
	 * freq: how many times this prefix show up before
	 */

	int i;
	for (i = 0; i < size; ++i) {
		prefix += nums[i];

		/* prefix - target won't lead to core dump */
		if (prefix >= target) {
			count += freq[prefix - target];
			/*
			 * freq[prefix - target];
			 * current_prefix - target aka old_prefix + target == current_prefix
			 * it can tell use how many subarray with sum is target between curr_prefix and old_prefix
			 */
		}
		++freq[prefix];
		/*
		 * this prefix show up one more times, add into frequency table
		 */
	}

	free(freq);

	return count;
}

int main()
{
	int nums[] = {1,0,1,0,1};
	int size = sizeof(nums) / sizeof(nums[0]);
	int target = 2;
	int res = numSubarraysWithSum(nums, size, target);
	printf("%d\n", res);
	return 0;
}
