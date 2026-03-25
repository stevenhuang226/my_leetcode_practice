#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int triangleNumber(int *nums, int numsSize);
int comparation(const void *a, const void *b);
int main()
{
	int a[4] = {2,2,3,4};
	int size = 4;
	printf("%d", triangleNumber(a, size));
	return 0;
}

int comparation(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int triangleNumber(int *nums, int numsSize)
{
	qsort(nums, numsSize, sizeof(int), comparation);
	int total = 0;
	int rm;

	for (rm = numsSize - 1; rm > 1; rm--) {
		int l = 0;
		int r = rm - 1;
		for (; l < r;) {
			if (nums[l] + nums[r] > nums[rm]) {
				total += r - l;
				r--;
			}
			else {
				l++;
			}
		}
	}

	return total;
}
