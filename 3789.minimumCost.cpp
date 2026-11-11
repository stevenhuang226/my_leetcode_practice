#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int64_t minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
		int64_t totalCost = 0;

		totalCost += (int64_t)min(need1, need2) * min(costBoth, cost1 + cost2);
		if (need1 > need2) {
			int64_t diff = need1 - need2;
			totalCost += min(costBoth, cost1) * diff;
		} else {
			int64_t diff = need2 - need1;
			totalCost += min(costBoth, cost2) * diff;
		}

		return totalCost;
	}
};
