#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct {
	int left;
	int right;
} Item;

static inline int min(int left, int right)
{
	return MIN(left, right);
}

int *solveQueries(int *nums, int num_size,
	int *queries, int queries_size,
	int *ret_size)
{
	int exp_max = 0;
	for (int i = 0; i < num_size; ++i) {
		exp_max = MAX(exp_max, nums[i]);
	}
	exp_max += 8;

	int32_t *prev = malloc(exp_max * sizeof(int));
	memset(prev, 0xff, exp_max * sizeof(int));
	int32_t *first = malloc(exp_max * sizeof(int));
	memset(first, 0xff, exp_max * sizeof(int));

	Item *items = malloc(num_size * sizeof(Item));
	memset(items, 0xff, num_size * sizeof(Item));

	for (int id = 0; id < num_size; ++id) {
		int num = nums[id];
		int L = prev[num];
		int R = first[num];

		items[id].left = L;
		items[id].right = R;

		prev[num] = id;

		if (L >= 0) {
			items[L].right = id;
		}

		if (first[num] < 0) {
			first[num] = id;
		}
	}

	for (int n = 0; n < exp_max; ++n) {
		int L = prev[n];
		if (L < 0) continue;

		int F = first[n];
		items[F].left = L;
	}

	int *result = malloc(queries_size * sizeof(int));

	for (int i = 0; i < queries_size; ++i) {
		int target = queries[i];

		int left = items[target].left;
		int right = items[target].right;

		if (left == -1 || right == -1) {
			result[i] = -1;
			continue;
		}

		int L_dist = min(
			(target - left + num_size) % num_size,
			(num_size - target + left));
		int R_dist = min(
			(right - target + num_size) % num_size,
			(num_size - target + right));

		result[i] = MIN(L_dist, R_dist);
	}

	free(items);
	free(prev);
	free(first);

	*ret_size = queries_size;
	return result;
}
