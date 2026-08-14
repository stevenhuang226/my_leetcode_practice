#include "shdstd.h"

#define INF32 (INT32_MAX / 4)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int *pool;
int memo[20][20];

int dfs(int left, int right)
{
	if (memo[left][right] != INF32)
		return memo[left][right];

	if (left == right) {
		memo[left][right] = pool[left];
		return pool[left];
	}

	int pick_left = pool[left] - dfs(left+1, right);
	int pick_right = pool[right] - dfs(left, right-1);

	int res = MAX(pick_left, pick_right);

	memo[left][right] = res;
	return res;
}

bool predictTheWinner(int *nums, int size)
{
	int exp_max = size;
	for (int i = 0; i < exp_max; ++i) {
		for (int i2 = 0; i2 < exp_max; ++i2) {
			memo[i][i2] = INF32;
		}
	}

	pool = nums;

	return (dfs(0, size-1) >= 0);
}
