/* This thing doesn't work because buffer is too small, but if we continue add the buffer, performance will be worse than the sort way, so I just give up */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int largestPerimeter(int *nums, int numsSize);
int main()
{
	int *a;
	a = malloc(6 * sizeof(int));
	a[0] = 1;
	a[1] = 2;
	a[2] = 2;
	a[3] = 4;
	a[4] = 18;
	a[5] = 8;
	printf("%d\n", largestPerimeter(a, 6));
	return 0;
}


int largestPerimeter(int *nums, int numsSize)
{
	int8_t *pool;
	pool = calloc(10001, sizeof(uint8_t));
	for (int i = 0; i < numsSize; i++) {
		pool[nums[i]]++;
	}

	int prev1 = -1;
	int prev2 = -1;
	for (int i = 9999; i >= 0; i--) {
		if (pool[i] == 0) {
			continue;
		}

		if (prev1 == -1) {
			prev1 = i;
			pool[i]--;
		}
		if (pool[i] == 0) {
			continue;
		}
		if (prev2 == -1) {
			prev2 = i;
			pool[i]--;
		}
		if (pool[i] == 0) {
			continue;
		}
		pool[i]--;
		if ( (i + prev2) > prev1) {
			free(pool);
			return i + prev2 + prev1;
		}
		prev1 = prev2;
		prev2 = i;
		if (pool[i] >= 0) {
			i++;
		}
	}

	return 0;
}
