#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int64_t spow(int64_t base, int64_t e, int64_t mod)
{
	int64_t res = 1;

	while (e) {

		if (e & 1) {
			res = (res * base) % mod;
		}

		base = (base * base) % mod;
		e >>= 1;
	}

	return res;
}

int *adj_head;
int *adj_next;
int *adj_to;
int edge_count;

void adj_link(const int parent, const int child)
{
	adj_to[edge_count] = child;
	adj_next[edge_count] = adj_head[parent];
	adj_head[parent] = edge_count;
	++edge_count;
}

int dfs_depth(int curr, int parent, int depth)
{
	int next = adj_head[curr];

	int best = depth;
	while (next >= 0) {
		int trg = adj_to[next];
		next = adj_next[next];

		if (trg == parent)
			continue;

		int child_depth = dfs_depth(trg, curr, depth+1);
		best = MAX(best, child_depth);
	}

	return best;
}

int assignEdgeWeights(int **edges, int size, int *col_size)
{
	int64_t mod = 1e9 + 7;
	int exp_max = size+2;

	adj_head = malloc(exp_max * sizeof(int));
	memset(adj_head, 0xff, exp_max * sizeof(int));
	adj_next = malloc(exp_max * 2 * sizeof(int));
	adj_to = malloc(exp_max * 2 * sizeof(int));
	edge_count = 0;

	for (int i = 0; i < size; ++i) {
		int left = edges[i][0];
		int right = edges[i][1];
		adj_link(left, right);
		adj_link(right, left);
	}

	int64_t depth = dfs_depth(1, -1, 0);

	free(adj_head);
	free(adj_next);
	free(adj_to);

	return spow(2, depth-1, mod);
}
