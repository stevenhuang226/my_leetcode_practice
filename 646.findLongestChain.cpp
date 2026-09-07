#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int findLongestChain(vector<vector<int>> &pairs) {
		sort(pairs.begin(), pairs.end(),
			[](const vector<int> &a, const vector<int> &b) {
				return a[1] < b[1];
			});

		int res = 0;
		int prevRight = INT_MIN;

		for (const auto &p : pairs) {
			if (prevRight < p[0]) {
				++res;
				prevRight = p[1];
			}
		}

		return res;
	}
};
