#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
	int id;
	int lim;
} Node;

int cmp_node(const void *l, const void *r)
{
	return ((Node *)l)->id - ((Node *)r)->id;
}

int maxBuilding(int n, int **restrictions, int restrictions_size, int *restrictions_col_size)
{
	int nodes_capacity = restrictions_size + 2;
	int nodes_size = nodes_capacity - 1;

	Node *nodes = malloc(nodes_capacity * sizeof(Node));

	nodes[0].id = 1;
	nodes[0].lim = 0;

	for (int i = 0; i < restrictions_size; ++i) {
		int id = restrictions[i][0];
		int lim = restrictions[i][1];

		nodes[i+1].id = id;
		nodes[i+1].lim = lim;
	}

	qsort(nodes, nodes_size, sizeof(Node), cmp_node);

	if (nodes[nodes_size-1].id != n) {
		nodes[nodes_size].id = n;
		nodes[nodes_size].lim = INT32_MAX;
		++nodes_size;
	}

	for (int i = 0; i < nodes_size - 1; ++i) {
		Node *L = &(nodes[i]);
		Node *R = &(nodes[i+1]);

		int height = L->lim;
		int dist = R->id - L->id;

		height += dist;

		R->lim = MIN(R->lim, height);
	}

	for (int i = nodes_size-1; i > 0; --i) {
		Node *L = &(nodes[i-1]);
		Node *R = &(nodes[i]);

		int height = R->lim;
		int dist = R->id - L->id;

		height += dist;

		L->lim = MIN(L->lim, height);
	}

	int best = 0;
	for (int i = 0; i < nodes_size - 1; ++i) {
		Node *L = &(nodes[i]);
		Node *R = &(nodes[i+1]);

		int dist = R->id - L->id;

		int peak = (L->lim + R->lim + dist) / 2;

		best = MAX(best, peak);
	}

	free(nodes);

	return best;
}
