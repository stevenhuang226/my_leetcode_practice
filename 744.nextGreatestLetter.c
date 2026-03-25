#include "shdstd.h"

#define INF32 ( INT32_MAX / 4 )
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
char nextGreatestLetter(char *letter, int size, char target)
{
	int smallest_letter = INF32;

	for (int i = 0; i < size; ++i) {
		if (letter[i] <= target) {
			continue;
		}
		smallest_letter = MIN(smallest_letter, letter[i]);
	}

	if (smallest_letter == INF32) {
		return letter[0];
	}

	return smallest_letter;
}
