#include "shdstd.h"

char *removeOuterParentheses(char *s) {
	int st = 0;

	char *res = malloc((strlen(s) + 1) * sizeof(char));
	int p = 0;

	while (*s) {
		if (*s == '(') {
			++st;
		}

		if (st != 1) {
			res[p++] = *s;
		}

		if (*s == ')') {
			--st;
		}

		++s;
	}

	res[p++] = '\0';

	return res;
}
