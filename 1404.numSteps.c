#include "shdstd.h"

int numSteps(char *s)
{
	ssize_t size = strlen(s);

	int steps = 0;
	int last_bit = 0;

	for (int i = size - 1; i > 0; --i) {
		if (((s[i] - '0') & 1) + last_bit == 0) {
			steps += 2;
			last_bit = 1;
		} else {
			steps += 1;
		}
	}

	return steps + last_bit;
}
