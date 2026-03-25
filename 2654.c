#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int gcd(int a, int b)
{
	while (b) {
		int tmp = b;
		b = a % b;
		a = tmp;
	}

	return a;
}

int minOperations(int *nums, int numsSize)
{
	int g = 0;
	int i,i2;

	int one_count = 0;
	for (i = 0; i < numsSize; ++i) {
		g = gcd(g, nums[i]);
		if (nums[i] == 1) ++one_count;
	}
	if (g > 1) return -1;
	if (one_count) {
		return numsSize - one_count;
	}

	int min_len = INT_MAX;
	for (i = 0; i < numsSize; ++i) {
		g = nums[i];
		for (i2 = i+1; i2 < numsSize; ++i2) {
			g = gcd(g, nums[i2]);
			if (g == 1) {
				int len = i2 - i;
				if (len < min_len) min_len = len;
				break;
			}
		}
	}

	return min_len + numsSize - 1;
}
