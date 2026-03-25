#include "shdstd.h"

int *asteroidCollision(int *asteroids, int size, int *p_ret_size)
{
	int *stack = malloc(size * sizeof(int));
	int top = -1;

	int *ret = malloc(size * sizeof(int));
	int ret_size = 0;

	for (int i = 0; i < size; ++i) {
		int asteroid = asteroids[i];

		if (asteroid > 0) {
			stack[++top] = asteroid;
			continue;
		}

		while (top > -1 && (stack[top] + asteroid) < 0) {
			--top;
		}
		if (top > -1 && (stack[top] + asteroid) == 0) {
			--top;
			continue;
		}
		if (top < 0) {
			ret[ret_size++] = asteroid;
		}
	}

	memcpy(ret + ret_size, stack, (top+1) * sizeof(int));
	free(stack);
	ret_size += (top + 1);
	*p_ret_size = ret_size;
	return ret;
}

int main()
{
	int arr[] = {5,10,-5};
	int size = sizeof(arr) / sizeof(arr[0]);
	int ret_size;
	int *res = asteroidCollision(arr, size, &ret_size);

	for (int i = 0; i < ret_size; ++i) {
		printf("%d ", res[i]);
	}
	printf("\n");
	free(res);

	return 0;
}
