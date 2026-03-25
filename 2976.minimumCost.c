#include "shdstd.h"

#define INF64 (INT64_MAX / 4)
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int64_t change_cost[26][26];

int64_t minimumCost(char *source,
		char *target,
		char *original, int original_size,
		char *changed, int changed_size,
		int *cost, int cost_size)
{
	for (int i = 0; i < 26; ++i) {
		for (int i2 = 0; i2 < 26; ++i2) {
			if (i == i2) {
				change_cost[i][i2] = 0;
			} else {
				change_cost[i][i2] = INF64;
			}
		}
	}

	for (int i = 0; i < cost_size; ++i) {
		int from = original[i] - 'a';
		int to = changed[i] - 'a';

		change_cost[from][to] = MIN(change_cost[from][to], cost[i]);
	}

	for (int mid = 0; mid < 26; ++mid) {
		for (int from = 0; from < 26; ++from) {
			for (int to = 0; to < 26; ++to) {
				if (change_cost[from][mid] == INF64 ||
						change_cost[mid][to] == INF64) {
					continue;
				}

				change_cost[from][to] = MIN(
						change_cost[from][to],
						change_cost[from][mid] + change_cost[mid][to]
						);
			}
		}
	}

	int64_t total_cost = 0;

	int str_size = strlen(source);

	for (int i = 0; i < str_size; ++i) {
		int src = source[i] - 'a';
		int trg = target[i] - 'a';

		if (src == trg) {
			continue;
		}

		if (change_cost[src][trg] == INF64) {
			return -1;
		}

		total_cost += change_cost[src][trg];
	}

	return total_cost;
}
