#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

int triangularSum(int *nums, int numsSize);
int main()
{
	int a[5] = {1,2,3,4,5};
	printf("\n%d\n", triangularSum(a, 5));
	return 0;
}

int triangularSum(int *nums, int numsSize)
{
	int i, ii;
	for (i = 0; i < (numsSize-1); i++) {
		for (ii = 0; ii < (numsSize - i - 1); ii++) {
			nums[ii] += nums[ii+1] % 10;
		}
	}

	return nums[0]%10;
}
