#include "shdstd-cpp.h"

using namespace std;

#define INF64 (INT64_MAX / 4)

class Solution {
public:

	int64_t minimumCost(string source, string target,
			vector<string> &original, vector<string> &changed,
			vector<int> &cost) {

		int cost_size = cost.size();
		unordered_map<int, unordered_map<string, unordered_map<string, int64_t>>> direct_cost;
		unordered_map<int, unordered_map<string, unordered_map<string, int64_t>>> min_cost;

		for (int i = 0; i < cost_size; ++i) {
			int len = original[i].size();

			int edge_cost = direct_cost[len][original[i]][changed[i]];
			if (edge_cost == 0 || edge_cost > cost[i]) {
				 direct_cost[len][original[i]][changed[i]] = cost[i];
			}
		}

		for (auto &len_entry : direct_cost) {
			int len = len_entry.first;
			unordered_map<string, int> str_id;
			vector<string> nodes;

			for (auto &from_entry : len_entry.second) {
				const string &from_str = from_entry.first;

				if (str_id.count(from_str) == 0) {
					int id = str_id.size();
					str_id[from_str] = id;
					nodes.push_back(from_str);
				}

				for (auto &to_entry : from_entry.second) {
					const string &to_str = to_entry.first;

					if (str_id.count(to_str) > 0) {
						continue;
					}

					int id = str_id.size();
					str_id[to_str] = id;
					nodes.push_back(to_str);
				}
			}

			int node_count = nodes.size();
			vector<vector<int64_t>> dist(node_count, vector<int64_t>(node_count, INF64));

			for (int i = 0; i < node_count; ++i) {
				dist[i][i] = 0;
			}

			for (auto &from_entry : len_entry.second) {
				int from_id = str_id[from_entry.first];
				for (auto &to_entry : from_entry.second) {
					int to_id = str_id[to_entry.first];
					dist[from_id][to_id] = min(dist[from_id][to_id],
							to_entry.second);
				}
			}

			for (int mid = 0; mid < node_count; ++mid) {
				for (int from = 0; from < node_count; ++from) {
					if (dist[from][mid] == INF64) {
						continue;
					}

					for (int to = 0; to < node_count; ++to) {
						if (dist[mid][to] == INF64) {
							continue;
						}

						int64_t new_cost = dist[from][mid] + dist[mid][to];
						dist[from][to] = min(dist[from][to], new_cost);
					}
				}
			}

			for (int from = 0; from < node_count; ++from) {
				for (int to = 0; to < node_count; ++to) {
					min_cost[len][nodes[from]][nodes[to]] = dist[from][to];
				}
			}
		}

		int source_size = source.size();

		vector<int64_t> convert_cost(source_size + 1, INF64);
		convert_cost[0] = 0;

		for (int i = 0; i < source_size; ++i) {
			if (source[i] == target[i]) {
				convert_cost[i+1] = min(convert_cost[i+1], convert_cost[i]);
			}
			if (convert_cost[i] == INF64) {
				continue;
			}
			for (auto &len_entry : min_cost) {
				int len = len_entry.first;
				if (i + len > source_size) {
					continue;
				}

				string src_sub = source.substr(i, len);
				string trg_sub = target.substr(i, len);

				auto from_it = len_entry.second.find(src_sub);
				if (from_it == len_entry.second.end()) continue;
				auto to_it = from_it->second.find(trg_sub);
				if (to_it == from_it->second.end()) continue;

				int64_t edge_cost = to_it->second;

				convert_cost[i+len] = min(convert_cost[i+len],
						convert_cost[i] + edge_cost);
			}
		}

		if (convert_cost[source_size] == INF64) {
			return -1;
		}
		return convert_cost[source_size];
	}
};
