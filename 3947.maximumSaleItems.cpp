#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct Item {
		int price;
		int limited;
	};

	struct ItemCompare {
		bool operator()(const Item &l, const Item &r) {
			return l.price > r.price;
		}
	};
public:
	int maximumSaleItems(vector<vector<int>> &items, int budget) {
		int mnPrice = INT32_MAX;
		unordered_map<int, int> freq;
		for (const vector<int> &v : items) {
			++freq[v[0]];
			mnPrice = min(mnPrice, v[1]);
		}

		priority_queue<Item, vector<Item>, ItemCompare> pq;

		for (const vector<int> &v : items) {
			int factor = v[0];
			int price = v[1];

			int extra = 0;
			for (const auto &[f, cnt] : freq) {
				if (f % factor == 0) {
					extra += cnt;
				}
			}
			--extra;

			if (extra > 0 && price < mnPrice * 2) {
				pq.push((Item){price, extra});
			}
		}

		int res = 0;
		while (!pq.empty() && budget > 0) {
			Item cur = pq.top();
			pq.pop();

			int cnt = min(cur.limited, budget / cur.price);

			budget -= cnt * cur.price;
			res += cnt * 2;

			if (cnt < cur.limited) break;
		}

		return res + budget / mnPrice;
	}
};
