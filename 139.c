#include "shdstd.h"

/*
 * mach a wordDict[i] -> check does it match all. If yes, mark end + 1.
 */

bool wordBreak(char *s, char **wordDict, int size)
{
	int str_size = strlen(s);

	int i, i2, ptr;

	int8_t mrk[str_size + 1];
	for (i = 1; i <= str_size; ++i) {
		mrk[i] = 0;
	}
	mrk[0] = 1;


	for (ptr = 0; ptr < str_size; ++ptr) {
		if (mrk[ptr] != 1) {
			// char *s cannot end with this index, skip
			continue;
		}

		/* check does char *s[ptr...n] match char *wordDict[i] */
		for (i = 0; i < size; ++i) {
			if (s[ptr] != wordDict[i][0]) {
				continue;
			}

			/* size of wordDict[i] */
			int length = strlen(wordDict[i]);
			int8_t brk = 0; // exit loop by break, default to false
			for (i2 = 1; i2 < length; ++i2) {
				if (ptr + i2 >= str_size) {
					brk = 1;
					break;
				}
				if (s[ptr + i2] != wordDict[i][i2]) {
					brk = 1;
					break;
				}
			}
			if (! brk) { // if not exit by break
				mrk[ptr + length] = 1;
				/*
				 * s can end with [ptr+lenght]
				 */
			}
		}
	}

	bool res = mrk[str_size];

	return res;
}

int main()
{
	char *s = "leetcode";

	int size = 2;
	int limit = 100;
	char **word = malloc(size * sizeof(char *));
	word[0] = malloc(limit * sizeof(char));
	strncpy(word[0], "leet", limit - 1);
	word[1] = malloc(limit * sizeof(char));
	strncpy(word[1], "code", limit - 1);

	printf("%d\n", wordBreak(s, word, size));
	for (int i = 0; i < size; ++i) {
		free(word[i]);
	}
	free(word);

	return 0;
}
