#include "shdstd.h"

char *findTheString(int **lcp, int lcp_size, int *lcp_col_size)
{
	int size = lcp_size;

	char *res = calloc((size+1), sizeof(char));

	char curr = 'a';

	for (int i = 0; i < size; ++i) {
		if (res[i] != 0) continue;

		if (curr > 'z') {
			res[0] = '\0';
			return res;
		}

		res[i] = curr;
		for (int i2 = i + 1; i2 < size; ++i2) {
			if (lcp[i][i2] > 0) {
				res[i2] = res[i];
			}
		}
		++curr;
	}

	for (int i = size-1; i >= 0; --i) {
		for (int i2 = size-1; i2 >= 0; --i2) {
			if (res[i] == res[i2]) {
				if (i == size-1 || i2 == size-1) {
					if (lcp[i][i2] == 1) continue;
					res[0] = '\0';
					return res;
				} else {
					if (lcp[i][i2] == lcp[i+1][i2+1] + 1) continue;
					res[0] = '\0';
					return res;
				}
			}
			if (res[i] != res[i2] &&
					lcp[i][i2] != 0) {
				res[0] = '\0';
				return res;
			}
		}
	}

	return res;
}
