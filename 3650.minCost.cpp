#include "shdstd-cpp.h"

#define INF32 (INT32_MAX / 4)

using namespace std;

int *adj_to;
int *adj_next;
int *adj_head;
int *adj_weight;

int edge_count;

int *dist;

class Solution {
	private:
		void create_edge(int from, int to, int weight)
		{
			adj_to[edge_count] = to;
			adj_next[edge_count] = adj_head[from];
			adj_weight[edge_count] = weight;
			adj_head[from] = edge_count;
			++edge_count;
		}
	public:
		int minCost(int nodes_size, vector<vector<int>>& edges)
		{
			int edges_size = edges.size();

			adj_to = (int *)malloc(edges_size * 2 * sizeof(int));
			adj_next = (int *)malloc(edges_size * 2 * sizeof(int));
			adj_head = (int *)malloc(nodes_size * sizeof(int));
			adj_weight = (int *)malloc(edges_size * 2 * sizeof(int));
			edge_count = 0;

			dist = (int *)malloc(nodes_size * sizeof(int));

			for (int i = 0; i < nodes_size; ++i) {
				adj_head[i] = -1;
				dist[i] = INF32;
			}

			for (int i = 0; i < edges_size; ++i) {
				int from = edges[i][0];
				int to = edges[i][1];
				int w = edges[i][2];
				create_edge(from, to, w);
				create_edge(to, from, w * 2);
			}

			priority_queue<
				pair<int, int>,
				vector<pair<int, int>>,
				greater<pair<int, int>>
					> pq;

			pq.push({0, 0});
			dist[0] = 0;

			while (! pq.empty()) {
				int cost = pq.top().first;
				int from = pq.top().second;
				pq.pop();

				if (cost > dist[from]) {
					continue;
				}

				int next_edge = adj_head[from];
				while (next_edge >= 0) {
					int to = adj_to[next_edge];
					int w = adj_weight[next_edge];
					next_edge = adj_next[next_edge];

					int new_cost = dist[from] + w;
					if (dist[to] <= new_cost) {
						continue;
					}
					dist[to] = new_cost;
					pq.push({new_cost, to});
				}
			}

			int last_cost = dist[nodes_size - 1];

			free(adj_to);
			free(adj_next);
			free(adj_head);
			free(adj_weight);
			free(dist);

			if (last_cost == INF32) {
				return -1;
			}
			return last_cost;
		}
};

int main()
{
	vector<vector<int>> edges = {
		{0,1,3},
		{3,1,1},
		{2,3,4},
		{0,2,2}
	};

	int nodes = 4;

	Solution solution;

	int ans = solution.minCost(nodes, edges);
	printf("%d\n", ans);

	return 0;
}
