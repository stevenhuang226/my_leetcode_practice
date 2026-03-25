#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

int maxFrequencyElements(int *nums, int numsSize);
int main()
{
	int32_t a[5] = {1,2,3,4,5};

	printf("%d", maxFrequencyElements(a, 5));
	return 0;
}

int maxFrequencyElements(int *nums, int numsSize)
{
	int32_t numsarr[101];
	memset(numsarr, 0, 101);
	int32_t max_freq = 0;
	int32_t max = 0;
	
	for (int i = 0; i < numsSize; i++) {
		if ((++numsarr[nums[i]]) > max_freq) {
			max_freq = numsarr[nums[i]];
		}
		if (nums[i] > max) {
			max = nums[i];
		}
	}
	max++;

	int32_t total_freq = 0;
	for (int i = 0; i < max; i++) {
		if (numsarr[i] == max_freq) {
			total_freq += max_freq;
		}
	}
	return total_freq;
}
