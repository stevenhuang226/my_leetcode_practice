#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int furthestDistanceFromOrigin(char *moves)
{
	int base = 0;
	int adj = 0;

	ssize_t len = strlen(moves);
	for (int i = 0; i < len; ++i) {
		char ch = moves[i];
		switch (ch) {
		case 'L':
			--base;
			break;
		case 'R':
			++base;
			break;
		case '_':
			++adj;
			break;
		}
	}

	return MAX(abs(base + adj), abs(base - adj));
}
