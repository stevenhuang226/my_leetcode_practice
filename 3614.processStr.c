#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define DUPLICATE '#'
#define REVERSE '%'
#define REMOVELAST '*'

static int64_t diff_len(const int64_t left, const int64_t right)
{
	return right - left + 1;
}

char processStr(char *s, int64_t k)
{
	if (k < 0) {
		return '.';
	}

	int64_t final_len = 0;

	int p = 0;
	int ch;

	int dptr = 1;

	while ((ch = s[p++]) != '\0') {
		if (ch == DUPLICATE) {
			final_len *= 2;
		} else if (ch == REMOVELAST) {
			if (final_len == 0) continue;
			--final_len;
		} else if (ch == REVERSE) {
			dptr = !dptr;
		} else {
			++final_len;
		}
	}

	if (k >= final_len) {
		return '.';
	}

	int64_t target = k;

	int64_t left, right;
	left = 0;
	right = final_len - 1;

	if (!dptr) {
		target = left + (right - target);
	}

	--p;
	while (p) {
		ch = s[--p];
		if (ch == DUPLICATE && dptr) {
			int64_t half = (right - left + 1) / 2;
			right -= half;
			if (target > right) {
				target -= half;
			}
		} else if (ch == DUPLICATE && !dptr) {
			int64_t half = (right - left + 1) / 2;
			left += half;
			if (target < left) {
				target += half;
			}
		} else if (ch == REVERSE) {
			dptr = !dptr;
		} else if (ch == REMOVELAST && dptr) {
			++right;
		} else if (ch == REMOVELAST && !dptr) {
			--left;
		} else if (dptr) {
			if (target == right) {
				return ch;
			}
			--right;
		} else if (!dptr) {
			if (target == left) {
				return ch;
			}
			++left;
		}
	}

	return '.';
}
