#include "shdstd.h"

typedef struct {
	int64_t cnt;
	int64_t wav;
} Node;

int digits[20];
int len;

Node memo[20][11][11];

Node dfs(int pos, int prev, int curr, int8_t tight)
{
	if (pos == len) {
		Node ret = {1, 0};
		return ret;
	}

	if (!tight && memo[pos][curr][prev].cnt >= 0)
		return memo[pos][curr][prev];

	int limit;
	if (tight) {
		limit = digits[pos];
	} else {
		limit = 9;
	}

	Node res = {0, 0};

	for (int d = 0; d <= limit; ++d) {
		int n_tight = tight && (d == limit);

		if (curr == 10 && d == 0) {
			Node child = dfs(pos+1, 10, 10, n_tight);

			res.cnt += child.cnt;
			res.wav += child.wav;

			continue;
		}

		if (curr == 10) {
			Node child = dfs(pos+1, 10, d, n_tight);

			res.cnt += child.cnt;
			res.wav += child.wav;

			continue;
		}

		int extra = 0;

		if (prev != 10) {
			if (prev < curr && curr > d)
				extra = 1;
			if (prev > curr && curr < d)
				extra = 1;
		}

		Node child = dfs(pos+1, curr, d, n_tight);

		res.cnt += child.cnt;
		res.wav += child.wav + child.cnt * extra;
	}

	if (!tight)
		memo[pos][curr][prev] = res;

	return res;
}

int64_t totalWaviness(int64_t start_num, int64_t end_num)
{
	--start_num;
	memset(memo, 0xff, sizeof(memo));
	int e = 20;
	len = 0;
	while (start_num) {
		digits[--e] = start_num % 10;
		start_num /= 10;
		++len;
	}
	int w = 0;
	for (; e < 20; ++e) {
		digits[w++] = digits[e];
	}

	Node start = dfs(0, 10, 10, 1);

	memset(memo, 0xff, sizeof(memo));
	e = 20;
	len = 0;
	while (end_num) {
		digits[--e] = end_num % 10;
		end_num /= 10;
		++len;
	}
	w = 0;
	for (; e < 20; ++e) {
		digits[w++] = digits[e];
	}

	Node end = dfs(0, 10, 10, true);

	return end.wav - start.wav;
}
