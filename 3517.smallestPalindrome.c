#include "shdstd.h"

#define CCR(a) ((a) - 'a')
char *smallestPalindrome(char *s)
{
	int len = strlen(s);

	char center = 0x00;
	if (len % 2 != 0) {
		center = s[len/2];
	}

	int freq[26];

	int half = len / 2;
	for (int i = 0; i < half; ++i) {
		++freq[CCR(s[i])];
	}

	char *res = malloc((len+1) * sizeof(char));
	int L = 0;
	int R = len-1;

	int p = 0;
	for (int i = 0; i < half; ++i) {
		while (freq[p] <= 0)
			++p;
		res[L++] = res[R--] = p + 'a';
		--freq[p];
	}

	if (center) {
		res[half] = center;
	}
	res[len] = '\0';

	return res;
}
