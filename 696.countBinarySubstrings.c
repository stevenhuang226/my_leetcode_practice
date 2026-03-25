#include "shdstd.h"

int countBinarySubstrings(char *s)
{
	ssize_t size = strlen(s);

	int last;
	int curr;
	last = 0;
	curr = 1;

	int res = 0;

	for (int i = 0; i < size - 1; ++i) {
		if (s[i] == s[i+1]) {
			++curr;
		} else {
			last = curr;
			curr = 1;
		}
		res += (curr <= last);
	}

	return res;
}
