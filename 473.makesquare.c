#include "shdstd.h"

int *length;
int sticks;
int total_sum;

int8_t memo[1 << 16];

int8_t dfs(uint32_t mask, int side, int curr_sum)
{
	if (memo[mask] != 0) {
		if (memo[mask] > 0)
			return true;
		return false;
	}

	int curr_side = curr_sum % side;

	if (curr_sum == total_sum) {
		return true;
	}

	for (int i = 0; i < sticks; ++i) {
		if (mask & 1 << i)
			continue;

		if (curr_side + length[i] > side)
			continue;

		if (dfs(mask | (1 << i), side, curr_sum + length[i])) {
			memo[mask] = 1;
			return true;
		}
	}

	memo[mask] = -1;
	return false;
}

bool makesquare(int *matchsticks, int size)
{
	memset(memo, 0x00, sizeof(memo));

	int sum = 0;
	for (int i = 0; i < size; ++i) {
		sum += matchsticks[i];
	}

	int side = sum / 4;
	if (side * 4 != sum)
		return false;

	length = matchsticks;
	sticks = size;
	total_sum = sum;

	return dfs(0, side, 0);
}
