#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

int minDistance(char *source, char *target)
{
	int src_size = strlen(source);
	int trg_size = strlen(target);

	int **dp = malloc((src_size + 1) * sizeof(int *));
	int *dp_flat = malloc((trg_size + 1) * (src_size + 1) * sizeof(int));

	int i, i2;
	for (i = 0; i <= src_size; ++i) {
		dp[i] = dp_flat + i * (trg_size + 1);
	}
	/* alloc dp 2d, (src_size+1) * (trg_size+1) */

	/*
	 * dp[a][b] => numbers of operations to make src[0...a] == trg[0...b]
	 */

	dp[0][0] = 0; /* it take nothing make src[0] == trg[0], because they didn't not even exists. Born for avoid read index:-1 */

	/* src */
	for (i = 1; i <= src_size; ++i) {
		dp[i][0] = i;
	} /* it's take <i> operation to make src lenght of <i> equal to a empty char[] (delete all element in it) */
	for (i = 1; i <= trg_size; ++i) {
		dp[0][i] = i;
	} /* it's take <i> operation to make empty src char[] equal to trg char[] (insert all element in trg into src) */

	for (i = 1; i <= src_size; ++i) {
		for (i2 = 1; i2 <= trg_size; ++i2) {
			if (source[i - 1] == target[i2 - 1]) {
				dp[i][i2] = dp[i-1][i2-1];
				continue;
			}

			int min = dp[i-1][i2-1] + 1;

			min = MIN(min, dp[i-1][i2] + 1);
			min = MIN(min, dp[i][i2-1] + 1);

			/*
			 * the three different operation we can have
			 * [i-1] [i2-1] + 1 => replace
			 * [i-1][i2] + 1 => delete
			 * [i][i2-1] + 1 => insert
			 */

			dp[i][i2] = min;
		}
	}

	int res = dp[src_size][trg_size];

	free(dp_flat);
	free(dp);

	return res;
}
