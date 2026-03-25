#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

int maxSumDivThree(int *nums, int size)
{
	int i;
	int min[3] = {-1, INT_MAX, INT_MAX};
	int most_min[3] = {-1, INT_MAX - 1, INT_MAX - 1};

	int sum = 0;

	for (i = 0; i < size; ++i) {
		int num = nums[i];
		sum += num;
		int r = num % 3;
		if (r == 0) {
			continue;
		}
		if (num < most_min[r]) {
			min[r] = most_min[r];
			most_min[r] = num;
			continue;
		}
		if (num < min[r]) {
			min[r] = num;
		}
	}

	switch (sum%3) {
		case 1:
			if (most_min[1] > min[2] + most_min[2]) {
				sum -= min[2] + most_min[2];
			} else {
				sum -= most_min[1];
			}
			break;
		case 2:
			if (most_min[2] > min[1] + most_min[1]) {
				sum -= min[1] + most_min[1];
			} else {
				sum -= most_min[2];
			}
			break;
		default:
			break;
	}

	return sum;
}
int main()
{
	int nums[] = {2,6,2,2,7};
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = maxSumDivThree(nums, size);

	printf("%d\n", res);

	return 0;
}
