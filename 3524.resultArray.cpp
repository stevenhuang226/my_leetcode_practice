#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	vector<long long> resultArray(vector<int> &nums, int k) {
		vector<long long> res(k, 0);

		vector<long long> dp(k*2, 0);

		for (int i = 0; i < nums.size(); ++i) {
			long long curr = nums[i];

			for (int r = 0; r < k; ++r) {
				dp[k + (r * curr) % k] += dp[r];
			}
			++dp[k + curr % k];
			for (int i2 = 0; i2 < k; ++i2) {
				dp[i2] = dp[i2 + k];
				dp[i2 + k] = 0;
				res[i2] += dp[i2];
			}
		}

		return res;
	}
};
