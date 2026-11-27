#include "shdstd-cpp.h"

using namespace std;

class Solution {
	int mxExpFactor = 1.5e3 + 8;
public:
	int maximumSaleItems(vector<vector<int>> &items, int budget) {
		int size = items.size();

		int minPrice = INT32_MAX;
		vector<int> freq(mxExpFactor, 0);
		for (const vector<int> &v : items) {
			++freq[v[0]];
			minPrice = min(minPrice, v[1]);
		}

		vector<int> mxCopies(budget+1, 0);
		for (const vector<int> &v : items) {
			int factor = v[0];
			int price = v[1];

			int gain = 0;
			for (int f = factor; f < mxExpFactor; f += factor) {
				gain += freq[f];
			}
			--gain;

			for (int b = budget; b >= price; --b) {
				mxCopies[b] = max(
					mxCopies[b],
					mxCopies[b-price] + gain + 1
				);
			}
		}

		int res = 0;
		int minPriceCnt = 0;
		for (int b = budget; b >= 0; b -= minPrice, ++minPriceCnt) {
			res = max(res, mxCopies[b] + minPriceCnt);
		}

		return res;
	}
};
