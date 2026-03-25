#include "shdstd-cpp.h"

class Solution
{
	public:
		int fib(int n)
		{
			if (n == 0) {
				return 0;
			}

			int dp[3];

			dp[0] = 0;
			dp[1] = 1;
			dp[2] = 1;

			for (int i = 1; i < n; ++i) {
				dp[2] = dp[0] + dp[1];
				dp[0] = dp[1];
				dp[1] = dp[2];
			}

			return dp[2];
		}
};
