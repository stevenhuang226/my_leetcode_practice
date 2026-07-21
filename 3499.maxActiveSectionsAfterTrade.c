#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int maxActiveSectionsAfterTrade(char *s)
{
	int len = strlen(s);

	int *seg = malloc(len * sizeof(int));
	int sp = 0;

	int zero_count = 0;

	for (int i = 0; i < len; ++i) {
		int count = 0;
		while (i < len && s[i] == '0') {
			++zero_count;
			++count;
			++i;
		}
		if (count) {
			seg[sp++] = count;
		}
	}

	int best = 0;
	for (int i = 0; i < sp - 1; ++i) {
		best = MAX(best, seg[i] + seg[i+1]);
	}

	free(seg);

	return (len - zero_count) + best;
}
