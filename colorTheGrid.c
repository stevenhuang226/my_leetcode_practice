#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

int colorTheGrid(int m, int n)
{
	uint64_t ans = 0;
	uint8_t **possible_table;
	*possible_table = malloc(m * sizeof(uint8_t *));
	for (int i = 0; i < m; ++i) {
		possible_table[i] = malloc(n * sizeof(uint8_t));
		memset(possible_table[i], 2, n);
	}
	possible_table[0][0] = 3;
}

int main()
{
	return 0;
}
