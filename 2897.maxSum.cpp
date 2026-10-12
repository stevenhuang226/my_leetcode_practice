#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int64_t mod = 1e9 + 7;
public:
	int maxSum(vector<int> &nums, int k) {
		int cnt[32] = {0};
		for (int n : nums) {
			for (int i = 0; i < 31; ++i) {
				if (n & 1 << i) {
					++cnt[i];
				}
			}
		}

		int res = 0;

		for (int i = 0; i < k; ++i) {
			int64_t n = 0;
			for (int i = 0; i < 31; ++i) {
				if (cnt[i]) {
					n |= 1 << i;
					--cnt[i];
				}
			}

			res = (res + (n * n) % mod) % mod;
		}

		return res;
	}
};
