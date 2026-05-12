#include "shdstd.h"

bool rotateString(char *s, char *goal)
{
	ssize_t len_s = strlen(s);
	ssize_t len_goal = strlen(goal);

	if (len_s != len_goal) {
		return false;
	}

	for (ssize_t off = 0; off < len_s; ++off) {
		int8_t mach = true;
		for (ssize_t i = 0; i < len_goal; ++i) {
			if (s[(i+off)%len_s] != goal[i]) {
				mach = false;
				break;
			}
		}
		if (mach) return true;
	}

	return false;
}
