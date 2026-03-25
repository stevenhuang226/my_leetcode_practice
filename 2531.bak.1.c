#include "shdstd.h"

#define CHAR_SIZE 26

bool isItPossible(char *word1, char *word2)
{
	int arr1[CHAR_SIZE] = {0};
	int arr2[CHAR_SIZE] = {0};

	int diff1, diff2;
	diff1 = diff2 = 0;

	int i = 0;
	while (word1[i] != '\0') {
		int c = word1[i++] - 'a';
		if (! arr1[c]) {
			++diff1;
		}
		++arr1[c];
	}
	i = 0;
	while (word2[i] != '\0') {
		int c = word2[i++] - 'a';
		if (! arr2[c]) {
			++diff2;
		}
		++arr2[c];
	}

	if (diff1 - diff2 > 2 || diff2 - diff1 > 2) {
		return false;
	}
_skip:
	int src, tgr;

	for (src = 0; src < CHAR_SIZE; ++src) {
		if (! arr1[src]) continue;
		for (tgr = 0; tgr < CHAR_SIZE; ++tgr) {
			if (! arr2[tgr]) continue;
			int d1 = diff1;
			int d2 = diff2;

			d1 -= (arr1[src] == 1);
			d1 += (arr1[tgr] == 0);

			d2 -= (arr2[tgr] == 1);
			d2 += (arr2[src] == 0);

			if (d1 == d2) {
				return true;
			}
		}
	}

	return false;
}

int main()
{
	char *a = "aa";
	char *b = "aa";

	bool res = isItPossible(a, b);

	printf("%d\n", res);
}
