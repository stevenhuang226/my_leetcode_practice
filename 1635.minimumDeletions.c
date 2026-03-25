#include "shdstd.h"

int minimumDeletions(char *s)
{
	int size = strlen(s);

	int b_count = 0;
	int del = 0;

	for (int i = 0; i < size; ++i) {
		if (s[i] == 'b') {
			++b_count;
			continue;
		}

		if (b_count > 0) {
			++del;
			--b_count;
		}
	}

	return del;
}
