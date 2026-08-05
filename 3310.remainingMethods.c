#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int *remainingMethods(int nodes_count, int k,
	int **invocations, int invocations_size, int *invocations_col_size,
	int *ret_size)
{
	int adj_capacity = MAX(nodes_count, invocations_size);

	int *adj_head = malloc(adj_capacity * sizeof(int));
	int *adj_to = malloc(adj_capacity * 2 * sizeof(int));
	int *adj_next = malloc(adj_capacity * 2 * sizeof(int));
	int edges_count = 0;
	memset(adj_head, 0xff, nodes_count * sizeof(int));

	for (int i = 0; i < invocations_size; ++i) {
		int from = invocations[i][0];
		int to = invocations[i][1];
		adj_to[edges_count] = to;
		adj_next[edges_count] = adj_head[from];
		adj_head[from] = edges_count;
		++edges_count;
	}

	int *queue = malloc(adj_capacity * sizeof(int));
	int front, back; front = back = 0;
	int8_t *visited = calloc(nodes_count, sizeof(int8_t));

	queue[front++] = k;
	visited[k] = true;
	while (front > back) {
		int curr = queue[back++];

		int nxt = adj_head[curr];
		while (nxt >= 0) {
			int t = adj_to[nxt];
			nxt = adj_next[nxt];

			if (visited[t])
				continue;

			visited[t] = true;
			queue[front++] = t;
		}
	}

	int *res = malloc(nodes_count * sizeof(int));
	int rp = 0;

	front = back = 0;
	for (int i = 0; i < nodes_count; ++i) {
		if (visited[i]) {
			visited[i] = false;
		} else {
			queue[front++] = i;
			visited[i] = true;
		}
	}

	for (int i = 0; i < invocations_size; ++i) {
		int from = invocations[i][1];
		int to = invocations[i][0];
		adj_to[edges_count] = to;
		adj_next[edges_count] = adj_head[from];
		adj_head[from] = edges_count;
		++edges_count;
	}

	while (front > back) {
		int curr = queue[back++];
		res[rp++] = curr;

		int nxt = adj_head[curr];
		while (nxt >= 0) {
			int t = adj_to[nxt];
			nxt = adj_next[nxt];

			if (visited[t]) {
				continue;
			}

			visited[t] = true;
			queue[front++] = t;
		}
	}

	*ret_size = rp;

	free(adj_head);
	free(adj_to);
	free(adj_next);
	free(queue);
	free(visited);

	return res;
}
