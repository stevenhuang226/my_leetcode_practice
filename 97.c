#include "shdstd.h"
/*
 * Can s3 generate by merge s1 and s2 ?
 */


bool isInterleave(char *a, char *b, char *trg)
{
	int sizea = strlen(a);
	int sizeb = strlen(b);
	int trg_size = strlen(trg);

	if (sizea + sizeb != trg_size) {
		return false;
	}

	int i,i2;

	int8_t **dp = malloc((sizea+1) * sizeof(int8_t *));
	int8_t *dp_flat = calloc(1, (sizea+1) * (sizeb+1) * sizeof(int8_t));

	for (i = 0; i <= sizea; ++i) {
		dp[i] = dp_flat + i * (sizeb + 1);
	}
	dp[0][0] = 1;

	for (i = 0; i <= sizea; ++i) {
		for (i2 = 0; i2 <= sizeb; ++i2) {
			if (i > 0 && a[i-1] == trg[i + i2 - 1]) {
				dp[i][i2] |= dp[i-1][i2];
			}
			if (i2 > 0 && b[i2-1] == trg[i + i2 - 1] && dp[i][i2-1]) {
				dp[i][i2] |= dp[i][i2-1];
			}
		}
	}

	int res = dp[sizea][sizeb];

	free(dp_flat);
	free(dp);

	return res;
}
