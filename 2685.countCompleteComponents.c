#include "shdstd.h"

typedef struct {
	int root;
	int size;
	int edges;
} UFNode;

typedef struct {
	int capacity;
	UFNode data[];
} UnionFind;

UnionFind *uf_create(int capacity)
{
	UnionFind *uf = malloc(sizeof(UnionFind) + capacity * sizeof(UFNode));
	for (int i = 0; i < capacity; ++i) {
		uf->data[i].root = i;
		uf->data[i].size = 1;
		uf->data[i].edges = 0;
	}
	uf->capacity = capacity;
	return uf;
}

int uf_find(UnionFind *uf, int target)
{
	int trg_root = uf->data[target].root;
	if (trg_root == target) {
		return target;
	}

	uf->data[target].root = uf_find(uf, trg_root);
	return uf->data[target].root;
}

void uf_union(UnionFind *uf, int a, int b)
{
	int root_a = uf_find(uf, a);
	int root_b = uf_find(uf, b);

	if (root_a == root_b) {
		++uf->data[root_a].edges;
		return;
	}

	if (uf->data[root_a].size > uf->data[root_b].size) {
		int tmp = root_a;
		root_a = root_b;
		root_b = tmp;
	}

	uf->data[root_a].root = root_b;
	uf->data[root_b].size += uf->data[root_a].size;
	uf->data[root_b].edges += uf->data[root_a].edges + 1;
}

int countCompleteComponents(int nodes, int **edges, int edges_size, int *edges_col_size)
{
	UnionFind *uf = uf_create(nodes+1);

	for (int i = 0; i < edges_size; ++i) {
		int a = edges[i][0];
		int b = edges[i][1];
		uf_union(uf, a, b);
	}

	int count = 0;
	for (int i = 0; i < nodes; ++i) {
		if (uf->data[i].root != i)
			continue;

		int size = uf->data[i].size;
		int edge_cnt = uf->data[i].edges;
		int want_edges = size * (size-1) / 2;

		if (want_edges == edge_cnt) {
			++count;
		}
	}

	free(uf);

	return count;
}
