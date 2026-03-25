#include "shdstd.h"

bool isItPossible(char *s1, char *s2)
{
	char c;
	int ptr = 0;

	int freq1[26] = {0};
	int8_t ds1 = 0;
	int df1 = 0;

	while ((c = s1[ptr++]) != '\0') {
		int pc = c - 'a';
		if (freq1[pc]) {
			ds1 = 1;
		} else {
			++df1;
		}
		++freq1[pc];
	}
	int freq2[26] = {0};
	int8_t ds2 = 0;
	int df2 = 0;
	ptr = 0;
	while ((c = s2[ptr++]) != '\0') {
		int pc = c - 'a';
		if (freq2[pc]) {
			ds2 = 1;
		} else  {
			++df2;
		}
		++freq2[pc];
	}

	if (abs(df1 - df2) > 4) {
		return false;
	}

	if (df1 == df2 && ds1 == 1 && ds1 == ds2) {
		return true;
	} else if (df1 == df2) {
		int i;
		for (i = 0; i < 26; ++i) {
			if ((freq1[i] > 0) != (freq2[i] > 0)) {
				goto _skip;
			}
		}
		return true;
	}
_skip:

	int i, i2;
	for (i = 0; i < 26; ++i) {
		if (! freq1[i]) continue;
		for (i2 = 0; i2 < 26; ++i2) {
			if (! freq2[i2]) continue;
			if (i == i2) continue;

			int d1 = df1;
			int d2 = df2;

			d1 -= freq1[i] == 1;
			d1 += freq1[i2] == 0;

			d2 -= freq2[i2] == 1;
			d2 += freq2[i] == 0;

			if (d1 == d2) {
				return true;
			}
		}
	}

	return false;
}
