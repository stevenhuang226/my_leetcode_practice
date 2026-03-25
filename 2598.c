#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int findSmallestInteger(int *nums, int numsSize, int value)
{
	int32_t *mod_arr;
	mod_arr = calloc(value, sizeof(int32_t));
	int i;
	for (i = 0; i < numsSize; i++) {
		int mod = ((nums[i] % value) + value) % value;
		mod_arr[mod]++;
	}

	int mex = 0;
	for (i = 0;;) {
		mod_arr[i]--;
		if (mod_arr[i++] < 0) {
			break;
		}
		mex++;
		if (i == value) i = 0;
	}
	return mex;
}

int main()
{
	int nums[] = {0,-3};
	int numsSize = sizeof(nums) / sizeof(nums[0]);
	int value = 4;

	int res = findSmallestInteger(nums, numsSize, value);
	printf("%" PRId32 "\n", res);

	return 0;
}
