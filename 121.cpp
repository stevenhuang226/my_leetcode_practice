#include "shdstd-cpp.h"

class Solution {
	public:
		int maxProfit(std::vector<int>& prices)
		{
			int profit = 0;
			int buy = INT_MAX;

			for (int i = 0; i < prices.size(); ++i) {
				int item = prices[i];
				buy = std::min(item, buy);

				profit = std::max(profit, item - buy);
			}

			return profit;
		}
};
