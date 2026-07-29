#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int64_t permutation(int *freq, int64_t sum, int64_t limit)
{
	int64_t res = 1;
	for (int i = 0; i < 26; ++i) {
		int curr = freq[i];
		if (curr <= 0)
			continue;

		curr = MIN(curr, sum-curr);

		int64_t comb = 1;

		for (int c = 0; c < curr; ++c) {
			comb = (comb * (sum - c)) / (c + 1);

			if (comb > limit)
				return limit + 1;
		}

		res *= comb;
		if (res > limit)
			return limit + 1;

		sum -= freq[i];
	}

	return res;
}

char *smallestPalindrome(char *s, int k)
{
	int len = strlen(s);
	int half = len / 2;

	int freq[26] = {0};
	int sum = 0;
	for (int i = 0; i < half; ++i) {
		++freq[s[i] - 'a'];
		++sum;
	}

	char odd_center = 0x00;
	if (len % 2) {
		odd_center = s[half];
	}

	int64_t remained = k;

	char *res = malloc((len + 1) * sizeof(char));
	res[0] = '\0';
	for (int i = 0; i < half; ++i) {
		int r = len - i - 1;

		for (int i2 = 0; i2 < 26; ++i2) {
			if (freq[i2] <= 0)
				continue;

			--freq[i2];
			--sum;

			int64_t ways = permutation(&(freq[0]), sum, remained);

			if (ways >= remained) {
				res[i] = i2 + 'a';
				res[r] = i2 + 'a';
				break;
			}

			remained -= ways;
			++freq[i2];
			++sum;
		}
	}
	res[len] = '\0';

	if (odd_center) {
		res[half] = odd_center;
	}

	return res;
}
