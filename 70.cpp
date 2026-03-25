#include "shdstd-cpp.h"

int climbStairs(int n)
{
	if (n == 1) return 1;

	int dp[3];
	dp[0] = 1;
	dp[1] = 1;
	for (int i = 2; i <= n; ++i) {
		dp[2] = dp[0] + dp[1];
		dp[0] = dp[1];
		dp[1] = dp[2];
	}

	int32_t res = dp[2];

	return res;
}

int main()
{
	int n;
	std::cin >> n;

	int res = climbStairs(n);
	
	std::cout << res << "\n";
}
