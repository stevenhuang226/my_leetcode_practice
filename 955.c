#include "shdstd.h"

int minDeletionSize(char **strs, int size)
{
	int delete = 0;

	int length = strlen(strs[0]);
	int8_t *ignore = calloc(1, size * sizeof(int8_t));

	for (int col = 0; col < length; ++col) {
		int8_t brk = 0;
		for (int i = 0; i < size - 1; ++i) {
			if (ignore[i]) {
				continue;
			}
			if (strs[i+1][col] < strs[i][col]) {
				++delete;
				brk = 1;
				break;
			}
		}

		if (brk) {
			continue;
		}

		for (int i = 0; i < size - 1; ++i) {
			if (strs[i+1][col] > strs[i][col]) {
				ignore[i] = true;
			}
		}
	}

	free(ignore);
	return delete;
}
