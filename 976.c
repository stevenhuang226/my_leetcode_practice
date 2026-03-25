#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

int main()
{
	return 0;
}

int compare(const void *a, const void *b)
{
	return *(int *)b - *(int *)a;
}

int largestPerimeter(int *nums, int numsSize)
{
	qsort(nums, numsSize, sizeof(int), compare);
	for (int i = 0; i < numsSize - 2; i++) {
		if (nums[i] >= nums[i+1] + nums[i+2]) {
			continue;
		}
		return nums[i] + nums[i+1] + nums[i+2];
	}
	return 0;
}
