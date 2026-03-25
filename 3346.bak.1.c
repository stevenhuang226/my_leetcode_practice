#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>

#define MAX_NUM 125001

int maxFrequency(int *nums, int numsSize, int k, int numOperations)
{
	int i,ii;
	uint32_t *curr_freq;
	uint32_t *prefix_freq;
	curr_freq = calloc(MAX_NUM, sizeof(uint32_t));
	prefix_freq = calloc(MAX_NUM, sizeof(uint32_t));

	uint32_t max = 0;

	if (numOperations != 0) goto _nz;

	for (i = 0; i < numsSize; ++i) {
		++curr_freq[nums[i]];
		if (curr_freq[nums[i]] > max) {
			max = curr_freq[nums[i]];
		}
	}
	goto _izsk;
_nz:
	for (i = 0; i < numsSize; ++i) {
		int curr = nums[i];
		++curr_freq[curr];
	}

	for (i = 0; i < MAX_NUM; ++i) {
		int freq_sum = curr_freq[i] + ((expe_freq[i] < numOperations) ? expe_freq[i] : numOperations);
		if (freq_sum > max) {
			max = freq_sum;
		}
	}

_izsk:

	free(curr_freq);
	free(expe_freq);

	return (int32_t)max;
}

int main()
{
	int arr[] = {1,4,5};
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	int k = 1;
	int num_operations = 2;

	int res = maxFrequency(arr, arr_size, k, num_operations);

	printf("%d\n", res);

	return 0;
}
