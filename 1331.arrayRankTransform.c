#include "shdstd.h"

typedef struct {
	int id;
	int val;
} Node;

int cmp_node(const void *l, const void *r)
{
	return ((Node *)l)->val - ((Node *)r)->val;
}

int *arrayRankTransform(int *arr, int size, int *ret_size)
{
	Node *nodes = malloc(size * sizeof(Node));

	for (int i = 0; i < size; ++i) {
		nodes[i].val = arr[i];
		nodes[i].id = i;
	}

	qsort(nodes, size, sizeof(Node), cmp_node);

	int *res = malloc(size * sizeof(int));
	*ret_size = size;

	int p = 0;
	int prev = -1000000;
	for (int i = 0; i < size; ++i) {
		int id = nodes[i].id;
		int curr = nodes[i].val;
		if (curr != prev) {
			++p;
		}

		prev = curr;
		res[id] = p;
	}

	free(nodes);

	return res;
}
