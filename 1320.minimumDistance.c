#include "shdstd.h"

#define KEY_TABLE_WIDTH 6
#define INF32 (INT32_MAX / 4)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int dist(char src, char dst)
{
	int src_x = (src - 'A') / KEY_TABLE_WIDTH;
	int src_y = (src - 'A') % KEY_TABLE_WIDTH;

	int dst_x = (dst - 'A') / KEY_TABLE_WIDTH;
	int dst_y = (dst - 'A') % KEY_TABLE_WIDTH;

	return (abs(src_x - dst_x) + abs(src_y - dst_y));
}

int minimumDistance(char *word)
{
	int length = strlen(word);
	if (length <= 2) {
		return 0;
	}

	int dp[length][26];
	for (int i = 0; i < length; ++i) {
		for (int i2 = 0; i2 < 26; ++i2) {
			dp[i][i2] = INF32;
		}
	}
	for (int i = 0; i < 26; ++i) {
		dp[0][i] = 0;
	}

	for (int i = 1; i < length; ++i) {
		int curr = word[i] - 'A';
		int prev = word[i-1] - 'A';

		int d = dist(prev, curr);
		for (int i2 = 0; i2 < 26; ++i2) {
			dp[i][i2] = MIN(dp[i][i2], dp[i-1][i2] + d);
			dp[i][prev] = MIN(dp[i][prev], dp[i-1][i2] + dist(i2, curr));
		}
	}

	int best = INF32;

	for (int i = 0; i < 26; ++i) {
		best = MIN(best, dp[length-1][i]);
	}

	return best;
}
