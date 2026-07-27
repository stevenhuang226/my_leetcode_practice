#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static inline int smax(const int a, const int b)
{
	return MAX(a, b);
}

int longestPalindromeSubseq(char *s)
{
	int len = strlen(s);

	if (len == 1)
		return 1;

	int **dp = malloc(len * sizeof(int *));
	int *dp_flat = calloc(1, len * len * sizeof(int));
	for (int i = 0; i < len; ++i) {
		dp[i] = dp_flat + i * len;
		dp[i][i] = 1;
	}

	int best = 0;
	for (int i = len-2; i >= 0; --i) {
		for (int i2 = i+1; i2 < len; ++i2) {
			if (s[i] == s[i2]) {
				dp[i][i2] = dp[i+1][i2-1] + 2;
			} else {
				dp[i][i2] = MAX(dp[i+1][i2], dp[i][i2-1]);
			}

			best = MAX(best, dp[i][i2]);
		}
	}

	free(dp_flat);
	free(dp);

	return best;
}
