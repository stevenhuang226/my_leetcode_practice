#include "shdstd.h"

int32_t countCollisions(char *directions)
{
	int32_t lp = 0;
	int32_t rp = 0;

	uint32_t lefts = 0;
	uint32_t rights = 0;

	uint32_t count = 0;

	char c;

	while ((c = directions[rp++]) != '\0') {
		if (c == 'R') {
			++rights;
			continue;
		}
		count += rights;
		rights = 0;
	}

	for (lp = rp - 1; lp >= 0; --lp) {
		c = directions[lp];
		if (c == 'L') {
			++lefts;
			continue;
		}
		count += lefts;
		lefts = 0;
	}

	return count;
}
