#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

static int sgcd(int a, int b)
{
	while (b) {
		int t = a % b;
		a = b;
		b = t;
	}
	return a;
}

int subsequencePairCount(int *nums, int size)
{
	int64_t mod = 1e9 + 7;
	int max_n = 1;
	for (int i = 0; i < size; ++i) {
		max_n = MAX(max_n, nums[i] + 1);
	}

	int **dp = malloc(max_n * sizeof(int *));
	int *dp_flat = calloc(1, max_n * max_n * sizeof(int));
	int **next = malloc(max_n * sizeof(int *));
	int *next_flat = calloc(1, max_n * max_n * sizeof(int));
	for (int i = 0; i < max_n; ++i) {
		dp[i] = dp_flat + i * max_n;
		next[i] = next_flat + i * max_n;
	}


	dp[0][0] = 1;

	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		for (int g1 = 0; g1 < max_n; ++g1) {
			for (int g2 = 0; g2 < max_n; ++g2) {
				if (dp[g1][g2] == 0)
					continue;
				int new_g1, new_g2;
				if (g1 == 0) {
					new_g1 = num;
				} else {
					new_g1 = sgcd(g1, num);
				}
				if (g2 == 0) {
					new_g2 = num;
				} else {
					new_g2 = sgcd(g2, num);
				}

				next[new_g1][g2] = (next[new_g1][g2] + dp[g1][g2]) % mod;
				next[g1][new_g2] = (next[g1][new_g2] + dp[g1][g2]) % mod;
				next[g1][g2] = (next[g1][g2] + dp[g1][g2]) % mod;
			}
		}

		int **tmp = dp;
		dp = next;
		next = tmp;

		memset(next[0], 0x00, max_n * max_n * sizeof(int));
	}

	int ans = 0;
	for (int i = 1; i < max_n; ++i) {
		ans = (ans + dp[i][i]) % mod;
	}

	free(dp_flat);
	free(dp);

	free(next_flat);
	free(next);

	return ans;
}
