#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

bool kLengthApart(int *nums, int numsSize, int k)
{
	int i;
	int ret = true;
	int last_one = -1000001;
	for (i = 0; i < numsSize; ++i) {
		if (nums[i] != 1) continue;

		/*printf("i: %d, last_one: %d\n", i, last_one);*/
		if (k > (i - last_one - 1)) {
			ret = false;
			break;
		}
		last_one = i;
	}

	return ret;
}

int main()
{
	int nums[] = {1,0,0,1,0,1};
	int k = 2;
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = kLengthApart(nums, size, k);

	printf("%d\n", res);

	return 0;
}
