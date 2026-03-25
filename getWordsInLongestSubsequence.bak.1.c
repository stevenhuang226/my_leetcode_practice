#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

char **getWordsInLongestSubsequence(char **words, int wordsSize, int *groups, int groupsSize, int *returnSize)
{
	char **ans = malloc(wordsSize * sizeof(char *));

	int ptr = 1;
	ans[0] = words[0];
	int last = groups[0];
	int last_index = 0;
	int last_length = strlen(words[0]);
	for (int i = 1; i < wordsSize; ++i) {
		if (groups[i] != last && strlen(words[i]) == last_length) {
			int8_t diff = 0;
			for (int ii = 0; ii < last_length; ii++) {
				if (diff == 1 &&
				words[i][ii] != words[last_index][ii]) {
					diff = -1;
					break;
				}
				if (diff == 0 &&
				words[i][ii] != words[last_index][ii]) {
					diff = 1;
				}
			}
			if (diff == -1) {
				continue;
			}
			ans[ptr] = words[i];
			ptr++;
			last = groups[i];
			last_index = i;
			last_length = strlen(words[i]);
			continue;
		}
		if (groups[i-1] != groups[i] && groups[i] != last) {
			last = groups[i-1];
			last_index = i - 1;
			last_length = strlen(words[i-1]);
		}
	}
	*returnSize = ptr;
	return ans;
}
