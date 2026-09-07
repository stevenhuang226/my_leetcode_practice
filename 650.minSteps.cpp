#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minSteps(int n) {
		vector<int> dp(n+1, 0);

		for (int i = 2; i <= n; ++i) {
			dp[i] = i;

			for (int i2 = 1; i2 < i; ++i2) {
				if (i % i2 == 0) {
					dp[i] = min(dp[i], dp[i2] + i / i2);
				}
			}
		}

		return dp[n];
	}
};
