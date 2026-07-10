#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX_LOG2 18
typedef struct {
	int id;
	int val;
} Node;

int cmp_node(const void *l, const void *r)
{
	return ((Node *)l)->val - ((Node *)r)->val;
}

int try_jump(int **jump, int from, int target)
{
	if (jump[MAX_LOG2-1][from] < target) {
		return -1;
	}

	int curr = from;
	int count = 0;

	for (int lg = MAX_LOG2-1; lg >= 0; --lg) {
		if (jump[lg][curr] < target) {
			count += (1 << lg);
			curr = jump[lg][curr];
		}
	}
	return count+1;
}

int *pathExistenceQueries(int n,
	int *nums, int nums_size, int max_diff,
	int **queries, int queries_size, int *queries_col_size,
	int *ret_size)
{
	Node *nodes = malloc(nums_size * sizeof(Node));
	for (int i = 0; i < nums_size; ++i) {
		nodes[i].val = nums[i];
		nodes[i].id = i;
	}
	qsort(nodes, nums_size, sizeof(Node), cmp_node);
	int *map = malloc(nums_size * sizeof(Node));
	for (int i = 0; i < nums_size; ++i) {
		int id = nodes[i].id;
		int val = nodes[i].val;
		map[id] = i;
	}

	int **jump = malloc(MAX_LOG2 * sizeof(int *));
	int *jump_flat = malloc(MAX_LOG2 * nums_size * sizeof(int));
	for (int i = 0; i < MAX_LOG2; ++i) {
		jump[i] = jump_flat + i * nums_size;
	}
	int L,R;
	for (L = 0, R = 0; L < nums_size; ++L) {
		while (R+1 < nums_size && nodes[R+1].val - nodes[L].val <= max_diff) {
			++R;
		}
		jump[0][L] = R;
	}
	for (int lg = 0; lg+1 < MAX_LOG2; ++lg) {
		for (int i = 0; i < nums_size; ++i) {
			jump[lg+1][i] = jump[lg][jump[lg][i]];
		}
	}

	free(nodes);

	int *res = malloc(queries_size * sizeof(int));
	*ret_size = queries_size;

	for (int i = 0; i < queries_size; ++i) {
		int a = map[queries[i][0]];
		int b = map[queries[i][1]];
		int from = MIN(a, b);
		int target = MAX(a, b);
		if (from == target) {
			res[i] = 0;
			continue;
		}
		res[i] = try_jump(jump, from, target);
	}

	free(map);
	free(jump_flat);
	free(jump);

	return res;
}
