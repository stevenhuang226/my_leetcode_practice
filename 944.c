#include "shdstd.h"

int minDeletionSize(char **strs, int size)
{
	int str_size = strlen(strs[0]);

	int count = 0;

	for (int i = 0; i < str_size; ++i) {
		for (int i2 = 1; i2 < size; ++i2) {
			if (strs[i2][i] < strs[i2-1][i]) {
				++count;
				break;
			}
		}
	}

	return count;
}
