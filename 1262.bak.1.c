#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

int maxSumDivThree(int *nums, int size)
{
	int min[3];
	min[0] = INT_MAX;
	min[1] = INT_MAX;
	min[2] = INT_MAX;

	int arr[3] = {0};

	int i;

	for (i = 0; i < size; ++i) {
		int num = nums[i];
		int mod = num % 3;

		arr[mod] += num;
		if (min[mod] > num) {
			min[mod] = num;
		}
	}

	int total = arr[0] + arr[1] + arr[2];
	printf("t:%d\n", total);
	printf("min[1]:%d, min[2]:%d\n", min[1], min[2]);
	if (total % 3 != 0) {
		total -= min[total%3];
	}

	return total;
}

int main()
{
	int nums[] = {2,6,2,2,7};
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = maxSumDivThree(nums, size);

	printf("%d\n", res);

	return 0;
}
