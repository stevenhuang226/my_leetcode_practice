#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */


char **removeAnagrams(char **words, int wordsSize, int *returnSize)
{
	int i,ii;
	char **res_words;

	res_words = malloc(wordsSize * sizeof(char *));
	for (i = 0; i < wordsSize; i++) {
		res_words[i] = malloc(101 * sizeof(char));
	}
	uint32_t last_arr[26] = {0};
	uint32_t char_arr[26] = {0};

	for (ii = 0; ii < strlen(words[0]); ii++) {
		last_arr[words[0][ii] - 'a']++;
	}

	int res_ptr = 0;
	int last_strlen = strlen(words[0]);

	strcpy(res_words[res_ptr++], words[0]);

	for (i = 1; i < wordsSize; i++) {
		for (ii = 0; ii < strlen(words[i]); ii++) {
			char_arr[words[i][ii] - 'a']++;
		}
		if (last_strlen == strlen(words[i])) {
			for (ii = 0; ii < 26; ii++) {
				if (char_arr[ii] != last_arr[ii]) break;
			}
			if (ii == 26) {
				memset(char_arr, 0x00, sizeof(char_arr));
				continue;
			}
		}
		strcpy(res_words[res_ptr++], words[i]);

		last_strlen = strlen(words[i]);
		for (ii = 0; ii < 26; ii++) {
			last_arr[ii] = char_arr[ii];
		}
		memset(char_arr, 0x00, sizeof(char_arr));
	}

	*returnSize = res_ptr;

	return res_words;
}
