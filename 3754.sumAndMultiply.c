#include "shdstd.h"

int64_t sumAndMultiply(int n)
{
	int64_t tmp = n;
	int64_t dig = 0;
	int64_t sum = 0;
	while (tmp) {
		int d = tmp % 10;
		if (d != 0) {
			dig = dig * 10 + d;
		}

		sum += d;

		tmp /= 10;
	}

	int64_t x = 0;
	while (dig) {
		x = (x * 10) + (dig % 10);
		dig /= 10;
	}

	return x * sum;
}
