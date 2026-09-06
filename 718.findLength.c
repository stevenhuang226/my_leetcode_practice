#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int findLength(int *numsa, int size_a, int *numsb, int size_b)
{
	int *longer;
	int *shorter;
	int long_len, short_len;

	if (size_a > size_b) {
		longer = numsa;
		shorter = numsb;

		long_len = size_a;
		short_len = size_b;
	} else {
		longer = numsb;
		shorter = numsa;

		long_len = size_b;
		short_len = size_a;
	}

	int *max_len = calloc(1, (short_len+1) * sizeof(int));

	int best = 0;
	for (int l = 0; l < long_len; ++l) {
		for (int s = short_len - 1; s >= 0; --s) {
			if (longer[l] == shorter[s]) {
				max_len[s+1] = max_len[s] + 1;
				best = MAX(best, max_len[s+1]);
			} else {
				max_len[s+1] = 0;
			}
		}
	}

	free(max_len);

	return best;
}
