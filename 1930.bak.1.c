#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SIZE 26
#define POS_SIZE 2

int countPalindromicSubsequence(char *s)
{
	int size = strlen(s);

	int *char_pos_flat = malloc(CHAR_SIZE * POS_SIZE * sizeof(int));
	int **char_pos = malloc(CHAR_SIZE * sizeof(int *));
	int i,i2;
	for (i = 0; i < CHAR_SIZE; ++i) {
		char_pos[i] = char_pos_flat + i * POS_SIZE;
		char_pos[i][0] = -1;
		char_pos[i][1] = -1;
	}
	uint32_t *btwe_char = calloc(CHAR_SIZE, sizeof(uint32_t));

	for (i = 0; i < size; ++i) {
		int c = s[i] - 'a';
		for (i2 = 0; i2 < CHAR_SIZE; ++i2) {
			if (char_pos[i2][0] < 0) {
				continue;
			}
			if (i2 == c && char_pos[c][0] == char_pos[c][1]) {
				continue;
			}
			printf("add char %c to %c ", c + 'a', i2 + 'a');
			btwe_char[i2] |= (0x01 << c);
			printf("%d\n", btwe_char[i2]);
		}
		char_pos[c][1] = i;
		if (char_pos[c][0] == -1) {
			printf("set init pos for %c at %d\n", c+'a', i);
			char_pos[c][0] = i;
		}
	}

	int count = 0;
	for (i = 0; i < CHAR_SIZE; ++i) {
		if (char_pos[i][0] == char_pos[i][1]) {
			continue;
		}
		uint32_t btwe = btwe_char[i];
		while (btwe) {
			btwe &= (btwe - 1);
			++count;
		}
		printf("%c %d\n", i+'a', count);
	}

	free(char_pos);
	free(char_pos_flat);
	free(btwe_char);

	return count;
}
