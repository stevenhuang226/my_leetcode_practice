#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int numSubarrayProductLessThanK(int *nums, int size, int k)
{
	uint64_t sum = 1; /* incase product bigger int32_t limit, so I'm using uint64_t here */
	int64_t count = 0;
	int l = 0;
	int r = 0;
	while (r < size) {
		sum *= nums[r++]; /* make right side bigger */
		/* if sum >= k, make window smaller by reduce left side aka l++ */
		while (sum >= k && l < r) {
			sum /= nums[l++];
		}
		/* if expend right side once a time, it will be (r-l)'s subarray a time */
		count += r - l;
	}
	return count;
}

int main()
{
	int nums[] = {10,5,2,6};
	int k = 100;
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = numSubarrayProductLessThanK(nums, size, k);

	printf("%d\n", res);

	return 0;
}
