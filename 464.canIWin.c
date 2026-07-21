#include "shdstd.h"

int8_t memo[1 << 20];
int max_choose;
int target;

int8_t win(const uint32_t curr, const int sum)
{
	int8_t m = memo[curr];
	if (m != 0) {
		if (m > 0) {
			return true;
		} else {
			return false;
		}
	}

	for (int i = 0; i < max_choose; ++i) {
		if (curr & 1 << i)
			continue;

		if (sum + i + 1 >= target) {
			memo[curr] = 1;
			return true;
		}

		uint32_t new = curr | 1 << i;

		if (!win(new, sum + i + 1)) {
			memo[curr] = 1;
			return true;
		}
	}

	memo[curr] = -1;
	return false;
}

bool canIWin(int _max_choose, int _target)
{
	max_choose = _max_choose;
	target = _target;

	int max_sum = (1 + max_choose) * max_choose / 2;
	if (max_sum < target) {
		return false;
	}

	memset(memo, 0, sizeof(memo));

	return win(0, 0);
}
