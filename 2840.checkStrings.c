#include "shdstd.h"

bool checkStrings(char *s1, char *s2)
{
	int size = strlen(s1);
	int s2_size = strlen(s2);

	if (size != s2_size) {
		return false;
	}

	int odd_freq[26] = {0};
	int even_freq[26] = {0};

	for (int i = 0; i < size; ++i) {
		int cha = s1[i] - 'a';
		int chb = s2[i] - 'a';

		if (i % 2 == 0) {
			++even_freq[cha];
			--even_freq[chb];
		} else {
			++odd_freq[cha];
			--odd_freq[chb];
		}
	}

	for (int i = 0; i < 26; ++i) {
		if (odd_freq[i] != 0 || even_freq[i] != 0) {
			return false;
		}
	}

	return true;
}
