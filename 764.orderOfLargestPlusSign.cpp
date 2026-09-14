#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int orderOfLargestPlusSign(int n, vector<vector<int>> &mines) {
		vector<vector<int>> order(n, vector<int>(n, INT32_MAX));
		for (vector<int> arr : mines) {
			int r = arr[1];
			int c = arr[0];
			order[r][c] = 0;
		}

		for (int r = 0; r < n; ++r) {
			int leftLen = 0;
			for (int c = 0; c < n; ++c) {
				if (order[r][c] > 0) {
					order[r][c] = min(order[r][c], ++leftLen);
				} else {
					leftLen = 0;
				}
			}

			int rightLen = 0;
			for (int c = n-1; c >= 0; --c) {
				if (order[r][c] > 0) {
					order[r][c] = min(order[r][c], ++rightLen);
				} else {
					rightLen = 0;
				}
			}
		}

		int best = 0;
		for (int c = 0; c < n; ++c) {
			int upLen = 0;
			for (int r = 0; r < n; ++r) {
				if (order[r][c] > 0) {
					order[r][c] = min(order[r][c], ++upLen);
				} else {
					upLen = 0;
				}
			}

			int downLen = 0;
			for (int r = n-1; r >= 0; --r) {
				if (order[r][c] > 0) {
					order[r][c] = min(order[r][c], ++downLen);
					best = max(best, order[r][c]);
				} else {
					downLen = 0;
				}
			}
		}

		return best;
	}
};
