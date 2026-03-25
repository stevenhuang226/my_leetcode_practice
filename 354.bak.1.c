#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int max(const int a, const int b)
{
	if (a > b) return a;
	return b;
}

int compare(const void *a, const void *b)
{
	int *ar = *(int **)a;
	int *br = *(int **)b;
	if (ar[0] == br[0]) {
		return br[1] - ar[1];
	}
	return ar[0] - br[0];
}

int maxEnvelopes(int **envelopes, int envelope_size, int *envelopes_col_size)
{
	qsort(envelopes, envelope_size, sizeof(int *), compare);
	int *dp = malloc((envelope_size+1) * sizeof(int));

	int i,i2;
	int res = 0;
	for (i = 0; i < envelope_size; ++i) {
		dp[i] = 1;
		int h = envelopes[i][1];
		for (i2 = 0; i2 < i; ++i2) {
			if (envelopes[i2][1] >= h) continue;
			dp[i] = max(dp[i], dp[i2] + 1);
		}
		res = max(res, dp[i]);
	}
	free(dp);
	return res;
}
