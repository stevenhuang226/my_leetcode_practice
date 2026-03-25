#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>


char **getWordsInLongestSubsequence(char **words, int wordsSize, int *groups, int groupsSize, int *returnSize)
{
	// start from 0, then 1, continue like that...
	// if there is availd array be like 0,2,4,5. We don't need to start from 2, because it been run when start point is 0.
	int8_t recorded[wordsSize] = {0};
	int max_len = 0;

	for (int i = 0; i < wordsSize; i++) {
		recorded[i] = 1;

		// check if distance to end is big enougth to break the max_len recored.
}
