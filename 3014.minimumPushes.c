#include "shdstd.h"

int cmp_i32(const void *l, const void *r)
{
	return *(int *)r - *(int *)l;
}

int minimumPushes(char *word)
{
	int len = strlen(word);

	int freq[26] = {0};

	for (int i = 0; i < len; ++i) {
		int ch = word[i];
		++freq[ch - 'a'];
	}

	qsort(freq, 26, sizeof(int), cmp_i32);

	int res_count = 0;
	for (int i = 0; i < 8; ++i) {
		res_count += 1 * freq[i];
	}
	for (int i = 8; i < 16; ++i) {
		res_count += 2 * freq[i];
	}
	for (int i = 16; i < 24; ++i) {
		res_count += 3 * freq[i];
	}
	for (int i = 24; i < 26; ++i) {
		res_count += 4 * freq[i];
	}

	return res_count;
}
