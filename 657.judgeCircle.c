#include "shdstd.h"

bool judgeCircle(char *moves)
{
	int offset_x = 0;
	int offset_y = 0;

	int ch;
	int p = 0;
	while ((ch = moves[p++]) != '\0' && ch != EOF) {
		switch (ch) {
		case 'U':
			++offset_y;
			break;
		case 'D':
			--offset_y;
			break;
		case 'L':
			--offset_x;
			break;
		case 'R':
			++offset_x;
			break;
		}
	}

	if (offset_x == offset_y && offset_x == 0) {
		return true;
	} else {
		return false;
	}
}
