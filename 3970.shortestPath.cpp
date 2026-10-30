#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct DynamicArray {
		vector<int> dhead;
		vector<int> dnext;
		vector<int> dto;
		vector<int> dweight;
		int edgesCount;

		explicit DynamicArray(size_t sz) {
			dhead = vector<int>(sz, -1);
			dnext = vector<int>(sz * 2);
			dto = vector<int>(sz * 2);
			dweight = vector<int>(sz * 2);
			edgesCount = 0;
		}

		void link(int from, int to, int weight) {
			dto[edgesCount] = to;
			dweight[edgesCount] = weight;
			dnext[edgesCount] = dhead[from];
			dhead[from] = edgesCount;
			++edgesCount;
		}
	};
public:
	int shortestPath(int n, vector<vector<int>> &edges, string labels, int k) {
		DynamicArray darr = DynamicArray(max(n, (int)edges.size()) + 8);

		for (vector<int> &e : edges) {
			darr.link(e[0], e[1], e[2]);
		}

		using state = tuple<int, int, int>;

		priority_queue<state, vector<state>, greater<state>> waitEdges;

		vector<vector<int>> dist(n, vector<int>(k+1, INT32_MAX));
		int res = INT32_MAX;

		waitEdges.push((state){0, 0, 1});

		dist[0][1] = 0;

		while (!waitEdges.empty()) {
			auto [currWeight, currId, currConsecutive] = waitEdges.top();
			waitEdges.pop();

			if (currWeight != dist[currId][currConsecutive])
				continue;

			if (currId == n-1) {
				res = min(res, currWeight);
				continue;
			}

			int nxt = darr.dhead[currId];
			while (nxt >= 0) {
				int trg = darr.dto[nxt];
				int trgWeight = darr.dweight[nxt];
				nxt = darr.dnext[nxt];

				int consecutive = 1;
				if (labels[trg] == labels[currId]) {
					consecutive = currConsecutive + 1;
				}

				if (consecutive > k)
					continue;

				int nextWeight = currWeight + trgWeight;
				if (nextWeight >= dist[trg][consecutive])
					continue;

				dist[trg][consecutive] = nextWeight;

				waitEdges.push((state){
					nextWeight,
					trg,
					consecutive
				});
			}
		}

		if (res == INT32_MAX)
			return -1;
		return res;
	}
};
