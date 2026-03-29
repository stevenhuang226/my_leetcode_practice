#include "shdstd.h"

bool canBeEqual(char *s1, char *s2)
{
	int size = 4; // given by problem

	int odd_freq[26] = {0};
	int even_freq[26] = {0};

	for (int i = 0; i < size; ++i) {
		int ch = s1[i] - 'a';

		if (i % 2 == 0) {
			++even_freq[ch];
		} else {
			++odd_freq[ch];
		}
	}

	for (int i = 0; i < size; ++i) {
		int ch = s2[i] - 'a';

		if (i % 2 == 0) {
			--even_freq[ch];
		} else {
			--odd_freq[ch];
		}
	}

	for (int i = 0; i < 26; ++i) {
		if (odd_freq[i] != 0 || even_freq[i] != 0) {
			return false;
		}
	}

	return true;
}
