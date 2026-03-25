#include "shdstd.h"

#define RETURN_LIMIT 100004
#define STACK_SIZE 10004


typedef struct {
	int start;
	int times;
} Node;

char *decodeString(char *s)
{
	char *ret = malloc(RETURN_LIMIT * sizeof(char));
	int ret_size = 0;

	Node *stack = malloc(STACK_SIZE * sizeof(Node));
	int top = -1;

	int tmp = 0;

	int i = 0;
	char c;
	while ((c = s[i++]) != '\0') {
		if (c >= '0' && c <= '9') {
			tmp *= 10;
			tmp += c - '0';
			continue;
		}

		if (c >= 'a' && c <= 'z') {
			ret[ret_size++] = c;
			continue;
		}

		if (c == '[') {
			stack[++top].start = ret_size;
			stack[top].times = tmp;
			tmp = 0;
			continue;
		}

		int start = stack[top].start;
		int length = ret_size - start;
		int times = stack[top--].times;
		for (int i = 1; i < times; ++i) {
			memcpy(
				ret + start + (length * i),
				ret + start,
				length
			);
		}

		ret_size += length * (times - 1);
		continue;
	}

	ret[ret_size] = '\0';
	free(stack);

	return ret;
}
