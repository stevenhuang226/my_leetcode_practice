#include "shdstd.h"

int comp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

bool closeStrings(char *stra, char *strb)
{
	int mrka[26];
	int mrkb[26];
	memset(mrka, 0x00, sizeof(mrka));
	memset(mrkb, 0x00, sizeof(mrkb));

	int i = 0;
	char ca;
	char cb;
	while ((ca = stra[i]) != '\0' && (cb = strb[i]) != '\0') {
		++mrka[ca - 'a'];
		++mrkb[cb - 'a'];

		++i;
	}
	if (stra[i] != '\0' || strb[i] != '\0') {
		return false;
	}

	for (i = 0; i < 26; ++i) {
		if ((mrka[i] > 0) != (mrkb[i] > 0)) {
			return false;
		}
	}

	qsort(mrka, 26, sizeof(int), comp);
	qsort(mrkb, 26, sizeof(int), comp);

	for (i = 0; i < 26; ++i) {
		if (mrka[i] != mrkb[i]) {
			return false;
		}
	}

	return true;
}
