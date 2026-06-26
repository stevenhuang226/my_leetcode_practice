#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
typedef struct {
	int capacity;
	int ptr;
	uint64_t data[];
} MinStack;

uint64_t pack(int min, int val)
{
	return (uint64_t)(uint32_t)min << 32 | (uint64_t)(uint32_t)val;
}

MinStack *minStackCreate() {
	int exp_max = 3e4 + 8;
	MinStack *stack = malloc(sizeof(MinStack) + exp_max * sizeof(uint64_t));

	stack->capacity = exp_max;
	stack->ptr = -1;

	return stack;
}

int minStackGetMin(MinStack *stack)
{
	if (stack->ptr < 0) {
		return INT32_MAX;
	}

	return (int)(stack->data[stack->ptr] >> 32);
}

void minStackPush(MinStack *stack, int value)
{
	int curr_min = minStackGetMin(stack);
	curr_min = MIN(curr_min, value);
	stack->data[++stack->ptr] = pack(curr_min, value);
}

void minStackPop(MinStack *stack)
{
	if (stack->ptr >= 0) {
		--stack->ptr;
	}
}

int minStackTop(MinStack *stack)
{
	uint64_t src = stack->data[stack->ptr];
	int val = (int)(src & (uint64_t)UINT32_MAX);

	return val;
}

void minStackFree(MinStack *stack)
{
	free(stack);
}
