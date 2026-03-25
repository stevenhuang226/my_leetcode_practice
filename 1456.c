#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MOD 1000000007
#define INF8 (INT8_MAX / 4)
#define INF16 (INT16_MAX / 4)
#define INF32 (INT32_MAX / 4)
#define INF64 (INT64_MAX / 4)
#define NEG_INF8 -(INF8)
#define NEG_INF16 -(INF16)
#define NEG_INF32 -(INF32)
#define NEG_INF64 -(INF64)

int maxVowels(char *s, int k)
{
	int l = 0;
	int r = k;

	int vowels = 0;
	int max;

	for (int i = 0; i < k; ++i) {
		switch (s[i]) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				++vowels;
				break;
		}
	}
	max = vowels;

	char c;
	while ((c = s[r++]) != '\0') {
		switch (c) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				++vowels;
				break;
		}
		switch(s[l++]) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				--vowels;
				break;
		}

		max = MAX(max, vowels);
	}

	return max;
}

int main()
{
	char *s = "abciiidef";
	int k = 3;

	int res = maxVowels(s, k);
	printf("%d\n", res);

	return 0;
}
