#include "shdstd-cpp.h"

#define INF32 (INT32_MAX / 4)
using namespace std;

class Solution {
public:
	int64_t minimumCost(string source, string target,
			vector<string> &original, vector<string> &changed,
			vector<int> &cost) {

		/* [len][original][change] = cost */
		unordered_map<int, unordered_map<string, unordered_map<string, int>>> direct_cost;

		unordered_map<int, unordered_map<string, unordered_map<string, int>>> min_cost;

		int cost_size = cost.size();
		for (int i = 0; i < cost_size; ++i) {
			int len = original[i].size();

			int &edge_cost = direct_cost[len][original[i]][changed[i]];

			if (edge_cost == 0) {
				edge_cost = cost[i];
			} else {
				edge_cost = min(edge_cost, cost[i]);
			}
		}
	}
};
