#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

char **getLongestSubsequence(char **words, int wordsSize, int *groups, int groupsSize, int *returnSize)
{
	char **ans = malloc(wordsSize * sizeof(char *));

	int ptr = 1;
	ans[0] = words[0];
	for (int i = 1; i < wordsSize; ++i) {
		if (groups[i] != groups[i-1]) {
			ans[ptr] = words[i];
			ptr++;
		}
	}
	*returnSize = ptr;
	return ans;
}

int main()
{
	return 0;
}
