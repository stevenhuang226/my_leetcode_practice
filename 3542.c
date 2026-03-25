#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STACK_LIM_SIZE 100

int minOperations(int *nums, int numsSize)
{
	/* every times stack pop, count += 1; */
	/*
	 * if nums[i] > stack.top => push;
	 * if nums[i] < stack.pop => count+= 1
	 */

	uint32_t static stack[STACK_LIM_SIZE];
	int ptr = 0;
	stack[ptr] = 0;

	int count = 0;
	int i;
	for (i = 0; i < numsSize; ++i) {
		while (nums[i] < stack[ptr]) {
			--ptr;
			++count;
		}
		if (nums[i] > stack[ptr]) {
			stack[++ptr] = nums[i];
		}
	}
	count += ptr;
	return count;
}

int main()
{
	int arr[] = {3,5,1};
	int size = sizeof(arr) / sizeof(arr[0]);

	int ans = minOperations(arr, size);
	printf("%d\n", ans);

	return 0;
}
