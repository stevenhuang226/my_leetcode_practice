#include "shdstd.h"

int evalRPN(char **tokens, int tokens_size)
{
	int *stack = malloc(tokens_size * sizeof(int));
	int top = -1;

	for (int i = 0; i < tokens_size; ++i) {
		char *str = tokens[i];

		if (str[0] == '+') {
			stack[top-1] += stack[top];
			--top;
		} else if (str[0] == '-' && str[1] == '\0') {
			stack[top-1] -= stack[top];
			--top;
		} else if (str[0] == '*') {
			stack[top-1] *= stack[top];
			--top;
		} else if (str[0] == '/') {
			stack[top-1] /= stack[top];
			--top;
		} else {
			stack[++top] = atoi(str);
		}
	}

	int res = stack[0];

	free(stack);

	return res;
}
