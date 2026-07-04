#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define INF32 (INT32_MAX / 4)

typedef struct {
	int capacity;
	int parent[];
} UnionFind;

UnionFind *uf_create(int capacity)
{
	UnionFind *uf = malloc(sizeof(UnionFind) + capacity * sizeof(int));
	for (int i = 0; i < capacity; ++i) {
		uf->parent[i] = i;
	}
	uf->capacity = capacity;

	return uf;
}

int uf_find(UnionFind *uf, int target)
{
	if (uf->parent[target] == target) {
		return target;
	}

	uf->parent[target] = uf_find(uf, uf->parent[target]);

	return uf->parent[target];
}

void uf_merge(UnionFind *uf, int a, int b)
{
	int root_a = uf_find(uf, a);
	int root_b = uf_find(uf, b);

	if (root_a == root_b)
		return;

	uf->parent[root_a] = root_b;
}

int minScore(int trg, int **roads, int roads_size, int *roads_col_size)
{
	UnionFind *uf = uf_create(MAX(trg, roads_size));

	uint32_t *nodes_min = malloc(trg * sizeof(uint32_t));
	memset(nodes_min, 0xff, trg * sizeof(uint32_t));
	for (int i = 0; i < roads_size; ++i) {
		int a = roads[i][0] - 1;
		int b = roads[i][1] - 1;
		int w = roads[i][2];

		nodes_min[a] = MIN(nodes_min[a], w);
		nodes_min[b] = MIN(nodes_min[b], w);

		uf_merge(uf, a, b);
	}

	int best = INT32_MAX;
	int root = uf_find(uf, 0);
	for (int i = 0; i < trg; ++i) {
		if (uf_find(uf, i) != root)
			continue;

		best = MIN(nodes_min[i], best);
	}

	free(uf);
	free(nodes_min);

	return best;
}
