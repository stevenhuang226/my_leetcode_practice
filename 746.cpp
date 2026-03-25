#include "shdstd-cpp.h"

class Solution
{
public:
	int minCostClimbingStairs(std::vector<int>& cost)
	{
		int size = cost.size();
		for (int i = 2; i < size; ++i) {
			cost[i] += std::min(cost[i-1], cost[i-2]);
		}
		return std::min(cost[size-1], cost[size-2]);
	}
};
