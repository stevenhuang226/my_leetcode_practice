#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <inttypes.h>

#define MAX_NUM 125001

int maxFrequency(int *nums, int numsSize, int k, int numOperations)
{
	uint32_t *freq;
	uint32_t *pre;
	freq = calloc(MAX_NUM, sizeof(uint32_t));
	pre = calloc(MAX_NUM, sizeof(uint32_t));

	uint32_t max = 0;

	int max_num = INT_MIN;

	int i;

	for (i = 0; i < numsSize; ++i) {
		++freq[nums[i]];
		if (freq[nums[i]] > max) {
			max = freq[nums[i]];
		}
		if (nums[i] > max_num) max_num = nums[i];
	}

	if (k == 0 || numOperations == 0) goto _skip;

	max_num += k;
	
	pre[0] = freq[0];
	for (i = 1; i < max_num ; ++i) {
		pre[i] = pre[i-1] + freq[i];
		int left = (i - 2 * k - 1) > 0 ? (i - 2 * k - 1) : 0;
		int mid = (i - k) > 0 ? (i - k) : 0;

		uint32_t lr_sum = (pre[i] - pre[left] - freq[mid] < numOperations) ? pre[i] - pre[left] - freq[mid] : numOperations;
		lr_sum += freq[mid];

		if (lr_sum > max) max = lr_sum;
	}

_skip:
	free(freq);
	free(pre);

	return max;
}

int main()
{
	int arr[] = {2,27,123,32,127,124,160,153,99,134};
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	int k = 2;
	int num_operations = 2;

	int res = maxFrequency(arr, arr_size, k, num_operations);

	printf("%d\n", res);

	return 0;
}
