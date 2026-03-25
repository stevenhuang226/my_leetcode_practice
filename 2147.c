#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

int numberOfWays(char *corrider)
{
	if (corrider[1] == '\0') {
		return 0;
	}

	char c;
	int ptr = 0;

	int64_t sum = 1;
	int64_t gap = 1;

	int8_t has_seat = 0;
	int8_t never_seat = 1;


	while ((c = corrider[ptr++]) != '\0') {
		if (c == 'S' && ! has_seat) {
			never_seat = 0;
			has_seat = 1;
			sum *= gap;
			sum %= MOD;
			continue;
		} else if (c == 'P') {
			continue;
		}

		has_seat = 0;
		gap = 1;
		while (corrider[ptr] == 'P') {
			++ptr;
			++gap;
		}
	}

	if (has_seat || never_seat) {
		return 0;
	}

	return sum;
}

int main()
{
	char *corrider = "PPSPSP";

	int res = numberOfWays(corrider);

	printf("%d\n", res);

	return 0;
}
