#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int minimumDistance(int *nums, int size)
{
	int exp_max = size;
	for (int i = 0; i < size; ++i) {
		exp_max = MAX(exp_max, nums[i]);
	}
	exp_max += 8;

	int *adj_head = malloc(exp_max * sizeof(int));
	int *adj_next = malloc(exp_max * 2 * sizeof(int));
	int *adj_to = malloc(exp_max * 2 * sizeof(int));
	int link_count = 0;
	int *count = calloc(exp_max, sizeof(int));

	memset(adj_head, 0xff, exp_max * sizeof(int));

	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		++count[num];

		adj_to[link_count] = i;
		adj_next[link_count] = adj_head[num];
		adj_head[num] = link_count;
		++link_count;
	}

	int best = INT32_MAX;
	for (int i = 0; i < exp_max; ++i) {
		if (count[i] < 3) continue;

		int i0, i1, i2;

		int next = adj_head[i];

		i1 = adj_to[next];
		next = adj_next[next];
		i2 = adj_to[next];
		next = adj_next[next];

		while (next >= 0) {
			i0 = i1;
			i1 = i2;
			i2 = adj_to[next];

			next = adj_next[next];

			best = MIN(best, abs(i2 - i0) * 2);
		}
	}

	free(adj_head);
	free(adj_next);
	free(adj_to);
	free(count);

	if (best == INT32_MAX) {
		return -1;
	}
	return best;
}
