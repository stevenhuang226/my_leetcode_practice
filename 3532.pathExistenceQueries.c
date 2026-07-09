#include "shdstd.h"

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

void uf_union(UnionFind *uf, int a, int b)
{
	int root_a = uf_find(uf, a);
	int root_b = uf_find(uf, b);

	if (root_a == root_b) {
		return;
	}

	uf->parent[root_a] = root_b;
}

int8_t uf_sameroot(UnionFind *uf, int a, int b)
{
	return (uf_find(uf, a) == uf_find(uf, b));
}

bool *pathExistenceQueries(int n,
int *nums, int nums_size, int max_diff,
int **queries, int queries_size, int *queries_col_size,
int *ret_size)
{
	UnionFind *uf = uf_create(nums_size + 8);

	int L,R;
	L = R = 0;

	for (L = 0; L < nums_size; ++L) {
		while (R < nums_size && (nums[R] - nums[L]) <= max_diff) {
			uf_union(uf, L, R);
			++R;
		}
	}

	int8_t *res = malloc(queries_size * sizeof(int8_t));

	for (int i = 0; i < queries_size; ++i) {
		int q_L = queries[i][0];
		int q_R = queries[i][1];

		res[i] = uf_sameroot(uf, q_L, q_R);
	}

	free(uf);

	*ret_size = queries_size;
	return (bool *)res;
}
