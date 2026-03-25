#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint32_t *zero_pos;
uint32_t *one_prefixes;

int numberOfSubstrings(char *s)
{
	int size = strlen(s);
	zero_pos = malloc(sizeof(uint32_t));
	one_prefixes = malloc(sizeof(uint32_t));

	int i;
	int one_prefix = 0, ptr = 0;
	for (i = 0; i < size; ++i) {
		int8_t num = s[i] - '0';
		one_prefix += num;
		one_prefixes[i] = one_prefix;
		if (num) continue;
		zero_pos[ptr++] = i;
	}

	int left, right;

	for (left = right = 0; left < size; ++left) {
	}
}
