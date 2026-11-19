#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minCut(string s) {
		int len = s.length();

		vector<int> dp(len+1, INT32_MAX / 4);
		dp[0] = 0;

		for(int c = 0; c < len; ++c) {
			// check it's odd expand
			int l, r;
			for (l = r = c; l >= 0 && r < len; --l, ++r) {
				if (s[l] != s[r]) break;

				dp[r+1] = min(dp[r+1], dp[l]+1);
			}
			// check it's even expand
			for (l = c, r = c + 1; l >= 0 && r < len; --l, ++r) {
				if (s[l] != s[r]) break;

				dp[r+1] = min(dp[r+1], dp[l]+1);
			}
		}

		return dp[len] - 1;
	}
};
