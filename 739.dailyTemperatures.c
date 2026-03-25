#include "shdstd.h"

int *dailyTemperatures(int *temp, int size, int *return_size)
{
	int *stack = malloc(size * sizeof(int));
	int top = -1;

	int *ret = calloc(size, sizeof(int));
	(*return_size) = size;

	stack[++top] = 0;

	for (int i = 0; i < size; ++i) {
		while (top >= 0 && temp[stack[top]] < temp[i]) {
			int prev_index = stack[top--];
			ret[prev_index] = i - prev_index;
		}
		stack[++top] = i;
	}
	free(stack);
	return ret;
}
