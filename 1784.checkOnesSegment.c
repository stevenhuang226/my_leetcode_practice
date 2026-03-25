#include "shdstd.h"

bool checkOnesSegment(char *s)
{
	if (strstr(s, "01")) {
		return false;
	} else {
		return true;
	}
}
