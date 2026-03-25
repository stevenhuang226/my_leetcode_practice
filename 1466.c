#include "shdstd.h"

#define DEF_TO -1

typedef struct Node Node;

struct Node {
	int to;
	int8_t cost;
	Node *next;
};

void append_target(Node **edges, int from, int to, int cost)
{
	Node *curr = edges[from];
	if (curr->to == DEF_TO) {
		curr->to = to;
		curr->cost = cost;
		return;
	}

	while (curr->next != NULL) {
		curr = curr->next;
	}

	curr->next = malloc(sizeof(Node));
	curr->next->to = to;
	curr->next->cost = cost;
	curr->next->next = NULL;

	return;
}

int minReorder(int n, int **connections, int size, int *col_size)
{
	Node **edges = malloc(n * sizeof(Node *));
	Node *edges_flat = malloc(n * sizeof(Node));

	for (int i = 0; i < n; ++i) {
		edges[i] = edges_flat + i;
		edges[i]->to = DEF_TO;
		edges[i]->next = NULL;
	}

	for (int i = 0; i < size; ++i) {
		int l = connections[i][0];
		int r = connections[i][1];

		append_target(edges, l, r, 1);
		append_target(edges, r, l, 0);
	}

	int counter = 0;

	int *quene = malloc(n * sizeof(int));
	int quene_size = 0;

	int *next = malloc(n * sizeof(int));
	int next_size = 0;

	int8_t *visited = calloc(1, n * sizeof(int8_t));

	quene[quene_size++] = 0;

	visited[0] = 1;

	while (quene_size > 0) {
		for (int i = 0; i < quene_size; ++i) {
			int from = quene[i];

			Node *curr = edges[from];
			if (curr->to == DEF_TO) {
				continue;
			}

			while (curr != NULL) {
				if (! visited[curr->to]) {
					counter += curr->cost;
					visited[curr->to] = 1;
					next[next_size++] = curr->to;
				}

				curr = curr->next;
			}
		}

		int *tmp = quene;
		quene = next;
		next = tmp;

		quene_size = next_size;
		next_size = 0;
	}

	free(quene);
	free(next);
	free(visited);

	for (int i = 0; i < n; ++i) {
		Node *curr = edges[i];
		if (curr->to == DEF_TO) continue;

		curr = curr->next;

		while (curr != NULL) {
			Node *fre = curr;
			curr = curr->next;
			free(fre);
		}
		free(curr);
	}

	free(edges_flat);
	free(edges);

	return counter;
}
