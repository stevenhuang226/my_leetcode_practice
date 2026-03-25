#include "shdstd.h"

#define EXP_SIZE 100

#define LIMIT 16

enum {
	LEFT = 0,
	RIGHT,
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

static char *result_flat;
static int32_t global_ptr;

static int32_t bits;

void res_write(uint16_t state)
{
	uint8_t i;
	uint16_t mask = 0b1000000000000000;

	state <<= (LIMIT - bits);

	for (i = 0; i < bits; ++i) {
		uint16_t parentheses = (state & mask) >> (LIMIT - 1);
		if (parentheses == LEFT) {
			result_flat[global_ptr++] = '(';
			//printf("%c", '(');
		} else {
			result_flat[global_ptr++] = ')';
			//printf("%c", ')');
		}
		state <<= 1;
	}
	result_flat[global_ptr++] = '\0';
	//printf("\n");

	return;
}

void dfs(uint16_t state,  uint8_t left_remain, uint8_t right_remain, uint8_t operation)
{
	state <<= 1;
	state |= (uint16_t)operation;
	if (left_remain == 0 && right_remain == 0) {
		res_write(state);
		return;
	}
	if (left_remain < right_remain) {
		dfs(state, left_remain , right_remain - 1, RIGHT);
	}

	if (left_remain > 0) {
		dfs(state, left_remain - 1, right_remain, LEFT);
	}
	return;
}

char **generateParenthesis(int n, int *return_size)
{
	int32_t expect_size = (0x01 << n) * n;

	printf("expect_size:%d\n", expect_size);

	bits = n * 2;
	result_flat = malloc(expect_size * (bits + 1) * sizeof(char));

	global_ptr = 0;
	dfs(0x0000, n, n, LEFT);

	int32_t size = global_ptr / (bits + 1);
	printf("true_size:%d\n", size);
	(*return_size) = size;

	char **result = malloc(size * sizeof(char *));

	int32_t i;
	for (i = 0; i < size; ++i) {
		result[i] = result_flat + i * (bits + 1);
	}

	return result;
}

int64_t main()
{
	int32_t n = 5;
	int32_t return_size;
	char **res = generateParenthesis(n, &return_size);

	free(res);

	return 0;
}
