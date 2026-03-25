#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
char *longestCommonPrefix(char **strs, int size)
{
	int min_cols = INT32_MAX;
	for (int i = 0; i < size; ++i) {
		min_cols = MIN(min_cols, strlen(strs[i]));
	}

	char *ret = malloc((min_cols+1) * sizeof(char));

	for (int c = 0; c < min_cols; ++c) {
		char chr = strs[0][c];
		for (int r = 1; r < size; ++r) {
			if (strs[r][c] != chr) {
				ret[c] = '\0';
				return ret;
			}
		}
		ret[c] = chr;
	}
	ret[min_cols] = '\0';
	return ret;
}
