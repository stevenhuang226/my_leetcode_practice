#include "shdstd.h"

#define INF64 (INT64_MAX / 4)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int64_t *cost_cache;
int nodes;

typedef struct {
	int edges_count;
	int *head;
	int *next;
	int *to;
	int *cost;
} Adjust;

Adjust *adj_create(int capacity)
{
	Adjust *adj = malloc(sizeof(Adjust));
	adj->head = malloc(capacity * sizeof(int));
	memset(adj->head, 0xff, capacity * sizeof(int));
	adj->next = malloc(capacity * 2 * sizeof(int));
	adj->to = malloc(capacity * 2 * sizeof(int));
	adj->cost = malloc(capacity * 2 * sizeof(int));
	adj->edges_count = 0;

	return adj;
}

void adj_free(Adjust *adj)
{
	free(adj->head);
	free(adj->next);
	free(adj->to);
	free(adj->cost);
	free(adj);
}

void adj_link(Adjust *adj, int from, int to, int cost)
{
	adj->to[adj->edges_count] = to;
	adj->cost[adj->edges_count] = cost;
	adj->next[adj->edges_count] = adj->head[from];
	adj->head[from] = adj->edges_count;
	++adj->edges_count;
}

int64_t check(Adjust *adj, int curr, int min_cost)
{
	if (curr == nodes - 1)
		return 0;
	if (cost_cache[curr] >= 0)
		return cost_cache[curr];

	int64_t ans = INF64;
	int nxt = adj->head[curr];
	while (nxt >= 0) {
		int to = adj->to[nxt];
		int cost = adj->cost[nxt];
		nxt = adj->next[nxt];

		if (cost < min_cost)
			continue;

		int64_t min_child_cost = check(adj, to, min_cost) + cost;
		ans = MIN(ans, min_child_cost);
	}

	cost_cache[curr] = ans;
	return ans;
}

void clean_cache()
{
	memset(cost_cache, 0xff, nodes * sizeof(int64_t));
}

int findMaxPathScore(int **edges, int edges_size, int *edges_col_size,
		bool *online, int online_size, int64_t k)
{
	nodes = online_size;
	Adjust *adj = adj_create(MAX(edges_size, nodes));
	cost_cache = malloc(nodes * sizeof(int64_t));

	for (int i = 0; i < edges_size; ++i) {
		int from = edges[i][0];
		int to = edges[i][1];
		int cost = edges[i][2];

		if (!online[from] || !online[to])
			continue;

		adj_link(adj, from, to, cost);
	}

	int left = 0;
	int right = INT32_MAX;

	while (left < right)
	{
		int mid = left + (right - left) / 2;

		clean_cache();
		int64_t min_poss = check(adj, 0, mid);

		if (min_poss <= k) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}

	adj_free(adj);
	free(cost_cache);

	if (left == INT32_MAX) {
		return -1;
	}
	return left - 1;
}
