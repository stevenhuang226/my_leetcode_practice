#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int climbStairs(int n, vector<int> &costs) {
		vector<uint64_t> dp(n+4, INT64_MAX);
		dp[0] = 0;

		for (int i = 0; i < n; ++i) {
			dp[i+1] = min(
				dp[i+1],
				costs[i] + dp[i] + 1
			);

			if (i+1 < n) {
				dp[i+2] = min(
					dp[i+2],
					costs[i+1] + dp[i] + 4
				);
			}

			if (i+2 < n) {
				dp[i+3] = min(
					dp[i+3],
					costs[i+2] + dp[i] + 9
				);
			}
		}

		return dp[n];
	}
};
