#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int minOperations(char *s)
{
	int len = strlen(s);

	int odd_one = 0;
	int odd_zero = 0;
	for (int i = 0; i < len; i += 2) {
		if (s[i] == '1') {
			++odd_one;
		} else {
			++odd_zero;
		}
	}

	int even_one = 0;
	int even_zero = 0;
	for (int i = 1; i < len; i += 2) {
		if (s[i] == '1') {
			++even_one;
		} else {
			++even_zero;
		}
	}

	return MIN(odd_one + even_zero, odd_zero + even_one);
}
