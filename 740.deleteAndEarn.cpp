#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int deleteAndEarn(vector<int> &nums) {
		vector<int> cnts((int)1e4 + 8, 0);
		int expMax = 0;
		for (int n : nums) {
			++cnts[n];
			expMax = max(expMax, n);
		}
		++expMax;

		int pre = 0;
		int cur = cnts[1];
		for (int i = 2; i < expMax; ++i) {
			int tmp = cur;
			cur = max(cur, pre + cnts[i] * i);
			pre = tmp;
		}

		return cur;
	}
};
