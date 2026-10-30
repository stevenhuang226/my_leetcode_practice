#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int maxProfit(vector<int> &prices) {
		size_t sz = prices.size();

		int firstBuy = -prices[0];
		int firstSell = 0;
		int secondBuy = INT32_MIN;
		int secondSell = 0;

		for (int p : prices) {
			firstBuy = max(firstBuy, -p);
			firstSell = max(firstSell, firstBuy + p);

			secondBuy = max(secondBuy, firstSell - p);
			secondSell = max(secondSell, secondBuy + p);
		}

		return secondSell;
	}
};
