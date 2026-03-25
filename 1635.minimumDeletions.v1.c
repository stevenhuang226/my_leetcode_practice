#include "shdstd.h"

#define INF32 (INT32_MAX / 4)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int minimumDeletions(char *s)
{
	int size = strlen(s);

	int a_count = 0;
	int b_count = 0;

	for (int i = 0; i < size; ++i) {
		if (s[i] == 'a') {
			++a_count;
		} else {
			++b_count;
		}
	}

	if (a_count == 0 || b_count == 0) {
		return 0;
	}

	int min_del = MIN(a_count, b_count);

	int a_prefix = 0;
	int b_prefix = 0;

	for (int i = 0; i < size; ++i) {
		if (s[i] == 'a') {
			++a_prefix;
		} else {
			++b_prefix;
		}
		int del = a_count - a_prefix + b_prefix;
		min_del = MIN(min_del, del);
	}

	return min_del;
}
