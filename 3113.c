#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>


int64_t numberOfSubarrays(int *nums, int size)
{
	int *stack = malloc(size * sizeof(int));
	int *freq = malloc(size * sizeof(int));

	int top = -1;

	int64_t cnt = 0;

	int i;
	for (i = 0; i < size; ++i) {
		int num = nums[i];
		/*
		 * if stack not empty, and top is smaller than num
		 */
		while (top >= 0 && stack[top] < num) {
			/*
			 * cnt += how many time this element show up before in these stack range (stack[0] ~ stack[top]
			 */
			cnt += freq[top--];
		}
		if (top >= 0 && stack[top] == num) {
			/*
			 * add how many this element show up before 
			 * (that how does subarray work, every new element will make *freq* new subarray)
			 */
			cnt += freq[top];
			++freq[top];
		} else {
			/*
			 * if stack[top] is bigger then num
			 * push num into stack, and set freq[top] to 1, because this is the first time this element show up in this stack range
			 */
			stack[++top] = num;
			freq[top] = 1;
		}
	}

	/*
	 * add reminded element into cnt
	 */
	while (top >= 0) {
		cnt += freq[top--];
	}

	free(freq);
	free(stack);

	return cnt;
}
