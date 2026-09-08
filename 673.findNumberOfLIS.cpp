#include "shdstd-cpp.h"

using namespace std;

class Solution {
	struct State {
		int len;
		int cnt;
	};
public:
	int findNumberOfLIS(vector<int> &nums) {
		vector<State> dp(nums.size(), (State){1,1});

		State best = {0, 0};
		for (int i = 0; i < nums.size(); ++i) {
			for (int i2 = 0; i2 < i; ++i2) {
				if (nums[i2] >= nums[i])
					continue;

				int newLen = dp[i2].len + 1;
				if (newLen > dp[i].len) {
					dp[i].len = newLen;
					dp[i].cnt = dp[i2].cnt;
				} else if (newLen == dp[i].len) {
					dp[i].cnt += dp[i2].cnt;
				}
			}

			if (dp[i].len > best.len) {
				best.len = dp[i].len;
				best.cnt = dp[i].cnt;
			} else if (dp[i].len == best.len) {
				best.cnt += dp[i].cnt;
			}
		}

		return best.cnt;
	}
};
