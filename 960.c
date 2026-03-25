#include "shdstd.h"


#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int minDeletionSize(char **strs, int size)
{
	int str_size = strlen(strs[0]);
	/*
	 * dp mean. If end with this char. How many col we can pick
	 */

	int *dp = malloc(str_size * sizeof(int));

	int r, l, i;
	/*
	 * r: where dp end
	 * l: where last dp to pick
	 * i: loop pre-str
	 */
	for (r = 0; r < str_size; ++r) {
		dp[r] = 1;
		for (l = 0; l < r; ++l) {
			int8_t brk = 0;
			for (i = 0; i < size; ++i) {
				if (strs[i][l] > strs[i][r]) {
					brk = 1;
					break;
				}
			}

			if (brk) continue;

			dp[r] = MAX(dp[r], dp[l] + 1);
		}
	}

	int max;
	for (i = 0; i < str_size; ++i) {
		max = MAX(max, dp[i]);
	}

	free(dp);

	return str_size - max;
}
