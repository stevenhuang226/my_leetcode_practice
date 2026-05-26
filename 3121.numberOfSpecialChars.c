#include "shdstd.h"

#define CU(x) (x - 'A')
#define CL(x) (x - 'a')
#define ISUP(x) ('A' <= x && x <= 'Z')
#define ISLO(x) ('a' <= x && x <= 'z')
int numberOfSpecialChars(char *word)
{
	int upper_freq[26] = {0};
	int lower_freq[26] = {0};

	int length = strlen(word);

	for (int i = 0; i < length; ++i) {
		int ch = word[i];

		if (ISUP(ch)) {
			++upper_freq[CU(ch)];
		} else if (ISLO(ch) && upper_freq[CL(ch)] > 0) {
			lower_freq[CL(ch)] = INT32_MIN;
		} else {
			++lower_freq[CL(ch)];
		}
	}

	int count = 0;
	for (int i = 0; i < 26; ++i) {
		if (upper_freq[i] > 0 && lower_freq[i] > 0) {
			++count;
		}
	}

	return count;
}
