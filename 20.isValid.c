#include "shdstd.h"

bool isValid(char *s) {
	size_t len = strlen(s);

	char *stack = malloc(len * sizeof(char));
	int top = -1;

	while (*s) {

		if (*s == '(' || *s == '[' || *s == '{') {
			stack[++top] = *s;
		} else if (top < 0 || *s - stack[top] > 2 || *s - stack[top] < 0) {
				free(stack); return false;
		} else {
			--top;
		}

		++s;
	}

	free(stack);
	return top == -1;
}
