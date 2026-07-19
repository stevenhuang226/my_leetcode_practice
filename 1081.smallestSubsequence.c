#include "shdstd.h"

#define CODE(a) ((a) - 'a')

char *smallestSubsequence(char *str)
{
	int len = strlen(str);

	int last[26];
	memset(last, 0xff, sizeof(last));

	int diff_count = 0;
	for (int i = len-1; i >= 0; --i) {
		if (last[CODE(str[i])] < 0) {
			last[CODE(str[i])] = i;
			++diff_count;
		}
	}

	int stack[len+8];
	int top = -1;

	int8_t in_stack[26];
	memset(in_stack, false, sizeof(in_stack));

	for (int i = 0; i < len; ++i) {
		int chr = str[i];
		int cod = CODE(chr);

		if (in_stack[cod])
			continue;

		while (
			top >= 0 &&
			stack[top] > cod &&
			last[stack[top]] > i
		) {
			in_stack[stack[top]] = false;
			--top;
		}

		in_stack[cod] = true;
		stack[++top] = cod;
	}

	char *res = malloc((diff_count+1) * sizeof(char));
	for (int i = 0; i <= top; ++i) {
		res[i] = stack[i] + 'a';
	}
	res[diff_count] = '\0';

	return res;
}
