#include "shdstd.h"

#define DEF_FROM -1

typedef struct Node Node;

struct Node {
	int from;
	Node *next;
};

int minReorder(int n, int **connections, int size, int *col_size)
{
	Node **edges = malloc(n * sizeof(Node *));
	Node *edges_flat = malloc(n * sizeof(Node));

	for (int i = 0; i < n; ++i) {
		edges[i] = edges_flat + i;
		edges[i]->from = DEF_FROM;
		edges[i]->next = NULL;
	}

	for (int i = 0; i < size; ++i) {
		int from = connections[i][0];
		int to = connections[i][1];

		Node *curr = edges[i];

		if (curr->from == DEF_FROM) {
			curr->from = from;
			continue;
		}

		while (curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = malloc(sizeof(Node));
		curr->next->from = from;
		curr->next->next = NULL;
	}

	int counter = 0;

	int *quene[i]
}
