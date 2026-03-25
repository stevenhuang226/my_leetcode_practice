#include "shdstd-cpp.h"

class Solution
{
public:
	bool divisorGame(int n)
	{
		int dp[n+1];

		dp[0] = false;
		dp[1] = false;

		for (int i = 2; i <= n; ++i) {
			dp[i] = false;
			for (int x = 1; x < i; ++x) {
				if (i % x == 0 && ! dp[i - x]) {
					dp[i] = true;
					break;
				}
			}
		}

		return dp[n];
	}
};
