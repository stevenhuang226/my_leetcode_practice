#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
	int u;
	int v;
	int weight;
} Edge;

Edge *no_must_edges;
int *root;

int cmpEdge(const void *l, const void *r)
{
	int lw = (*(Edge *)l).weight;
	int rw = (*(Edge *)r).weight;

	return rw - lw;
}

void un_init(int size)
{
	root = malloc((size+1) * sizeof(int));
	for (int i = 0; i < size+1; ++i) {
		root[i] = i;
	}
}
int un_find(int target)
{
	if (root[target] == target) {
		return target;
	}

	root[target] = un_find(root[target]);
	return root[target];
}
void un_merge_root(int left_root, int right_root)
{
	if (left_root == right_root) {
		return;
	}

	root[left_root] = un_find(right_root);
}

void fre()
{
	free(root);
	free(no_must_edges);
}

int maxStability(int nodes, int **edges, int edges_size, int *edges_col_size, int max_update)
{
	un_init(nodes);
	no_must_edges = malloc(edges_size * sizeof(Edge));
	int no_must_count = 0;

	int components = nodes;

	int min_weight = INT32_MAX;

	for (int i = 0; i < edges_size; ++i) {
		int u = edges[i][0];
		int v = edges[i][1];
		int weight = edges[i][2];
		int8_t must = edges[i][3];

		if (! must) {
			no_must_edges[no_must_count].weight = weight;
			no_must_edges[no_must_count].u = u;
			no_must_edges[no_must_count].v = v;
			++no_must_count;
			continue;
		}

		int root_u = un_find(u);
		int root_v = un_find(v);

		if (root_u == root_v) {
			fre();
			return -1;
		}

		un_merge_root(root_u, root_v);
		--components;
		min_weight = MIN(min_weight, weight);
	}

	qsort(no_must_edges, no_must_count, sizeof(Edge), cmpEdge);

	for (int i = 0; i < no_must_count && components > 1; ++i) {
		int node_u = no_must_edges[i].u;
		int node_v = no_must_edges[i].v;
		int weight = no_must_edges[i].weight;
		if (components - 1 <= max_update) {
			weight *= 2;
		}

		int root_u = un_find(node_u);
		int root_v = un_find(node_v);

		if (root_u == root_v) continue;

		un_merge_root(root_u, root_v);
		--components;
		min_weight = MIN(min_weight, weight);
	}

	fre();
	if (components == 1) {
		return min_weight;
	}
	return -1;
}

/*
 * sort no-must with bit->small
 *
 * and push all must nodes into dsu
 *
 * start to loop no-must edges. If root is same. don't upgrade. If root isn't same upgrade it.
 */
