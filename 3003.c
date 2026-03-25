#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


int maxPartitionsAfterOperations(char *s, int k)
{
	if (k == 26) {
		return 1;
	}
	int i,ii;

	int size = strlen(s);
	int *left_mask = malloc(size * sizeof(int));
	int *left_rep = malloc(size * sizeof(int));
	int *left_parts = malloc(size * sizeof(int));

	int mask = 0;
	int rep_mask = 0;
	int parts = 1;
	for (i = 0; i < size; i++) {
		int bit = 1 << (s[i] - 'a');
		rep_mask |= mask & bit;
		mask |= bit;
		if (__builtin_popcount(mask) > k) {
			mask = bit;
			rep_mask = 0;
			parts++;
		}
		left_mask[i] = mask;
		left_rep[i] = rep_mask;
		left_parts[i] = parts;
	}

	int res = parts;
	mask = rep_mask = parts = 0;

	for (i = size - 1; i >= 0; i--) {
		int bit = 1 << (s[i] - 'a');
		rep_mask |= mask & bit;
		mask |= bit;

		int bit_count = __builtin_popcount(mask);
		if (bit_count > k) {
			mask = bit;
			rep_mask = 0;
			parts++;
			bit_count = 1;
		}
		if (bit_count == k) {
			if ((bit & rep_mask) &&
					(bit & left_rep[i]) &&
					(__builtin_popcount(left_mask[i]) == k) &&
					((left_mask[i] | mask) != 0x3FFFFFF)) {
				if (parts + left_parts[i] + 2 > res) res = parts + left_parts[i] + 2;
			} else if (rep_mask) {
				if (parts + left_parts[i] + 1 > res) res = parts + left_parts[i] + 1;
			}
		}
	}

	free(left_mask);
	free(left_rep);

	return res;
}

int main()
{
	char s[] = "baca";
	int k = 2;

	int result = maxPartitionsAfterOperations(s, k);
	printf("%d\n", result);

	return 0;
}
