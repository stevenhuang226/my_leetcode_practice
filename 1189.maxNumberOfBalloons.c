#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define CODE(a) ((a) - 'a')

int smin(const int a, const int b)
{
	return MIN(a, b);
}

int maxNumberOfBalloons(char *text)
{
	int freq[26];

	int len = strlen(text);
	for (int i = 0; i < len; ++i) {
		++freq[CODE(text[i])];
	}

	int min_pair = INT32_MAX;
	/*
	 * b * 1
	 * a * 1
	 * l * 2
	 * o * 2
	 * n * 1
	 */
	min_pair = smin(min_pair, freq[CODE('b')]);
	min_pair = smin(min_pair, freq[CODE('a')]);
	min_pair = smin(min_pair, freq[CODE('l')] / 2);
	min_pair = smin(min_pair, freq[CODE('o')] / 2);
	min_pair = smin(min_pair, freq[CODE('n')]);

	return min_pair;
}
