#include "shdstd.h"

#define CODE(a) ((a) - 'a')
int numberOfSubstrings(char *s)
{
	int len = strlen(s);

	int freq[3] = {0};

	int count = 0;
	int L, R;
	L = R = 0;
	while (L < len) {
		while (R < len && (freq[0] < 1 || freq[1] < 1 || freq[2] < 1)) {
			char ch = s[R++];
			++freq[CODE(ch)];
		}

		if (freq[0] >= 1 && freq[1] >= 1 && freq[2] >= 1) {
			count += len - R + 1;
		}

		char ch = s[L++];
		--freq[CODE(ch)];
	}

	return count;
}
