#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>


bool hasIncreasingSubarrays(int* nums, int numsSize, int k)
{
	if (k == 1) {
		return true;
	}
	int i;
	int combos = 1;
	bool combed = false;
	for (i = 1; i < numsSize; i++) {
		if (nums[i] > nums[i-1]) {
			combos++;
			continue;
		}
		if (combos >= 2 * k) {
			return true;
		}
		if (combos >= k) {
			if (combed) {
				return true;
			}
			combos = 1;
			combed = true;
			continue;
		}
		combed = false;
		combos = 1;
	}

	return (combed && combos >= k) || combos >= 2 * k;
}

int main()
{
	int a[] = {-15,-13,4,7};
	int size = sizeof(a)/sizeof(a[0]);
	int ans = hasIncreasingSubarrays(a,  size, 2);

	printf("%d\n", ans);
	
	return 0;
}
