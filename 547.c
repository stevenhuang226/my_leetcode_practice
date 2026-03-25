#include "shdstd.h"

int g_counter;

int find(int *parent, int target)
{
	if (parent[target] == target) {
		return target;
	}
	int new_root = find(parent, parent[target]);
	parent[target] = new_root;
	return parent[target];
}

void merge(int *parent, int dest, int src)
{
	int dest_root = find(parent, parent[dest]);
	int src_root = find(parent, parent[src]);

	if (dest_root == src_root) {
		return;
	}

	++g_counter;
	parent[dest_root] = src_root;

	return;
}

int findCircleNum(int **is_connected, int size, int *col_size)
{
	g_counter = 0;

	int *parent = malloc(size * sizeof(int));
	for (int i = 0; i < size; ++i) {
		parent[i] = i;
	}

	for (int i = 0; i < size; ++i) {
		for (int i2 = i + 1; i2 < size; ++i2) {
			if (! is_connected[i][i2]) continue;
			merge(parent, i, i2);
		}
	}

	free(parent);

	return size - g_counter;
}
