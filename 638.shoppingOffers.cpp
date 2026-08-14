#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	map<vector<int>, int> memo;

	int items;

	int cheapest(vector<int> &needs, const vector<int> &price, const vector<vector<int>> &special) {
		auto it = memo.find(needs);
		if (it != memo.end())
			return it->second;

		int best = 0;
		for (int i = 0; i < items; ++i) {
			best += needs[i] * price[i];
		}

		for (const vector<int> &offer : special) {
			int cost = offer[items];

			vector<int> next_needs = needs;
			bool brk = false;
			for (int i = 0; i < items; ++i) {
				next_needs[i] -= offer[i];
				if (next_needs[i] < 0) {
					brk = true;
					break;
				}
			}

			if (brk)
				continue;

			best = min(best, cost + cheapest(next_needs, price, special));
		}

		memo[needs] = best;

		return best;
	}

public:
	int shoppingOffers(vector<int> &price, vector<vector<int>> &special, vector<int> &needs) {
		this->items = price.size();

		return cheapest(needs, price, special);
	}
};
