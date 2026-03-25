#include "shdstd.h"

/*
 * mach a wordDict[i] -> check does it match all. If yes, mark end + 1.
 */

bool wordBreak(char *s, char **wordDict, int size)
{
	int str_size = strlen(s);
	int8_t *mrk = calloc(1, (str_size+1) * sizeof(int8_t));
	mrk[0] = 1;

	int i, i2, ptr;
	ptr = 0;

	while (ptr < str_size) {
		if (! mrk[ptr]) {
			++ptr;
			continue;
		}
		for (i = 0; i < size; ++i) {
			//printf("s [%d]: %c ", ptr, s[ptr]);
			//printf("word [%d]: %c\n", i, wordDict[i][0]);
			if (s[ptr] != wordDict[i][0]) {
				continue;
			}
			int child_size = strlen(wordDict[i]);
			//printf("wordDict[%d] size: %d\n", i, child_size);
			int8_t brk = 0;
			for (i2 = 1; i2 < child_size; ++i2) {
				if (ptr+i2 >= str_size) {
					brk = 1;
					break;
				}
				if (s[ptr + i2] != wordDict[i][i2]) {
					brk = 1;
					break;
				}
			}
			if (! brk) {
				mrk[ptr+child_size] = 1;
			}
		}

		++ptr;
	}

	bool res = mrk[str_size];

	free(mrk);

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
