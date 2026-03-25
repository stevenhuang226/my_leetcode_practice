#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

bool isOneBitCharacter(int *bits, int bitsSize)
{
	int i;
	for (i = 0; i < bitsSize - 1; ++i) {
		i += (bits[i] == 1);
	}

	return i == bitsSize - 1;
}
