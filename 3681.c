#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define BITS 32

int maxXorSubsequences(int *nums, int numsSize)
{
	int basis[BITS] = {0};

	int i,i2;
	for (i = 0; i < numsSize; ++i) {
		uint32_t num = nums[i];
		for (i2 = BITS - 1; i2 >= 0; --i2) {
			uint32_t stat = (num >> i2) & 1;
			if (! stat) continue;
			if (! basis[i2]) {
				basis[i2] = num;
				break;
			}
			num ^= basis[i2];
		}
	}

	uint32_t res = 0;
	for (i = BITS - 1; i >= 0; --i) {
		if ((res ^ basis[i]) <= res) continue;
		res ^= basis[i];
	}

	return (int)res;
}

int main()
{
	int nums[] = {1,2,3};
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = maxXorSubsequences(nums, size);

	printf("%d\n", res);

	return 0;
}
