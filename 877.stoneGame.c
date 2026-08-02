#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define EXP_MAX 508

int *arr;
int **memo;

int dfs(int left, int right)
{
	if (memo[left][right] != 0) {
		return memo[left][right];
	}

	if (left == right) {
		memo[left][right] = arr[left];
		return arr[left];
	}

	int left_diff = arr[left] - dfs(left+1, right);
	int right_diff = arr[right] - dfs(left, right-1);
	int max_diff = MAX(left_diff, right_diff);
	memo[left][right] = max_diff;
	return max_diff;
}

bool stoneGame(int *piles, int size)
{
	memo = malloc(size * sizeof(int *));
	int *memo_flat = calloc(1, size * size * sizeof(int));
	for (int i = 0; i < size; ++i) {
		memo[i] = memo_flat + i * size;
	}

	arr = piles;

	int diff = dfs(0, size-1);

	free(memo_flat);
	free(memo);

	return (diff > 0);
}
