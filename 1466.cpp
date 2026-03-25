#include "shdstd-cpp.h"

class Solution
{
public:
	int minReorder(int n, std::vector<std::vector<int>> &connections)
	{
		std::vector<std::vector<std::pair<int ,int>>> cost(n);

		for (auto &con : connections) {
			cost[con[0]].push_back({con[1], 1});
			cost[con[1]].push_back({con[0], 0});
		}
	}
};
