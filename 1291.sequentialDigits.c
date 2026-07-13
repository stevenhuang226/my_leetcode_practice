#include "shdstd.h"

int64_t spow(int64_t base, int64_t e)
{
	int64_t res = 1;
	while (e) {
		if (e & 1) {
			res = res * base;
		}

		base = base * base;
		e >>= 1;
	}
	return res;
}

int64_t left_shift_one(int64_t source, int64_t n)
{
	int64_t mask = spow(10, n-1);
	source = (source % mask) * 10 + (source % 10 + 1);
	return source;
}

int *sequentialDigits(int low, int high, int *ret_size)
{
	int tmp;

	int low_c = 0;
	int high_c = 0;
	tmp = low;
	while (tmp) {
		++low_c;
		tmp /= 10;
	}
	tmp = high;
	while (tmp) {
		++high_c;
		tmp /= 10;
	}

	int *res = malloc(((int)2e2 + 8) * sizeof(int));
	int ptr = 0;

	for (int i = low_c; i <= high_c; ++i) {
		int curr = 1;
		tmp = i;
		while (--tmp) {
			curr = curr * 10 + (curr % 10 + 1);
		}

		while (curr % 10 != 0 && curr <= high) {
			if (curr >= low) {
				res[ptr++] = curr;
			}
			curr = left_shift_one(curr, i);
		}
	}

	*ret_size = ptr;

	return res;
}
