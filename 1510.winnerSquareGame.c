#include "shdstd.h"

bool winnerSquareGame(int n)
{
	int8_t *win = calloc((n+1), sizeof(int));

	for (int i = 0; i <= n; ++i) {
		if (win[i])
			continue;

		for (int i2 = 1; i + i2 * i2 <= n; ++i2) {
			int curr = i + i2 * i2;

			win[curr] = true;
		}
	}

	int8_t res = win[n];

	free(win);

	return res;
}
