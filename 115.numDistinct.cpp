#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int numDistinct(string src, string trg) {
		vector<uint64_t> dp(trg.length()+1, 0);
		dp[0] = 1;

		for (int s = 0; s < src.length(); ++s) {
			for (int t = trg.length() - 1; t >= 0; --t) {
				if (src[s] == trg[t]) {
					dp[t+1] += dp[t];
				}
			}
		}

		return dp[trg.length()];
	}
};
