#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SIZE 26

int countPalindromicSubsequence(char *s)
{
	int i, i2;
	int size = strlen(s);

	int conformed[CHAR_SIZE] = {0};
	int temp[CHAR_SIZE] = {0};

	int start_pos[CHAR_SIZE];
	int close_pos[CHAR_SIZE];
	for (i = 0; i < CHAR_SIZE; ++i) {
		start_pos[i] = -1;
		close_pos[i] = -1;
	}

	for (i = 0; i < size; ++i) {
		int c = s[i] - 'a';
		if (i != start_pos[c]) {
			conformed[c] |= temp[c];
		}
		close_pos[c] = i;
		for (i2 = 0; i2 < CHAR_SIZE; ++i2) {
			if (start_pos[i2] < 0) {
				continue;
			}
			temp[i2] |= (0x01 << c);
		}
		if (start_pos[c] < 0) {
			start_pos[c] = i;
		}
	}

	int count = 0;
	for (i = 0; i < CHAR_SIZE; ++i) {
		int con = conformed[i];
		while (con) {
			con &= (con - 1);
			++count;
		}
	}

	return count;
}
