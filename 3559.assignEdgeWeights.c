#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

const int exp_lg = 17;

typedef struct {
	int *head;
	int *next;
	int *to;

	int edge_count;
} AdjArr;

AdjArr *adj;

void adj_create(int size)
{
	adj = malloc(sizeof(AdjArr));
	adj->head = malloc(size * sizeof(int));
	adj->next = malloc(size * 2 * sizeof(int));
	adj->to = malloc(size * 2 * sizeof(int));
	adj->edge_count = 0;
	memset(adj->head, 0xff, size * sizeof(int));
}

void adj_link(const int from, const int to)
{
	adj->to[adj->edge_count] = to;
	adj->next[adj->edge_count] = adj->head[from];
	adj->head[from] = adj->edge_count;
	++adj->edge_count;
}
void adj_autolink(const int a, const int b)
{
	adj_link(a, b);
	adj_link(b, a);
}
void adj_clean()
{
	free(adj->head);
	free(adj->next);
	free(adj->to);
	free(adj);
}

int64_t spow(int64_t base, int64_t e, int64_t mod)
{
	if (e < 0)
		return 0;

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

int *depth;
int **parent;

void dfs_build(int curr, int prev, int deep)
{
	depth[curr] = deep;
	parent[curr][0] = prev;

	int next = adj->head[curr];
	while (next >= 0) {
		int to = adj->to[next];
		next = adj->next[next];

		if (to == prev) continue;

		dfs_build(to, curr, deep+1);
	}
}

int lca(int u, int v)
{
	if (depth[u] < depth[v]) {
		int tmp = u;
		u = v;
		v = tmp;
	}

	int diff = depth[u] - depth[v];

	for (int l = 0; l < exp_lg; ++l) {
		if (diff & (1 << l)) {
			u = parent[u][l];
		}
	}

	if (u == v) return u;

	for (int l = exp_lg-1; l >= 0; --l) {
		if (parent[u][l] != parent[v][l]) {
			u = parent[u][l];
			v = parent[v][l];
		}
	}

	return parent[u][0];
}

int *assignEdgeWeights(int **edges, int edges_size, int *edges_col_size,
	int **queries, int queries_size, int *queries_col_size,
	int *ret_size)
{
	int exp_max = edges_size + 8;
	int nodes = edges_size + 1;
	int mod = 1e9 + 7;

	adj_create(exp_max);

	for (int i = 0; i < edges_size; ++i) {
		int a = edges[i][0];
		int b = edges[i][1];
		adj_autolink(a, b);
	}

	depth = malloc(exp_max * sizeof(int));
	parent = malloc(exp_max * sizeof(int *));
	int *parent_flat = malloc(exp_max * exp_lg * sizeof(int));
	for (int i = 0; i < exp_max; ++i) {
		parent[i] = parent_flat + i * exp_lg;
	}

	/* compute depth, parent[i][0] */
	dfs_build(1, -1, 0);

	/* build parent */
	for (int l = 1; l < exp_lg; ++l) {
		for (int node = 1; node <= nodes; ++node) {
			int mid = parent[node][l-1];

			if (mid == -1) {
				parent[node][l] = -1;
			} else {
				parent[node][l] = parent[mid][l-1];
			}
		}
	}

	int *res = malloc(queries_size * sizeof(int));
	*ret_size = queries_size;

	for (int i = 0; i < queries_size; ++i) {
		int node_u = queries[i][0];
		int node_v = queries[i][1];
		int ancestor = lca(node_u, node_v);

		int distance = depth[node_u] + depth[node_v] - 2 * depth[ancestor];

		res[i] = spow(2, distance-1, mod);
	}

	adj_clean();
	free(parent_flat);
	free(parent);

	free(depth);

	return res;
}
