#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int computeChange(const string &s, int L, int R) {
		int len = R-L+1;

		int minChange = INT32_MAX;
		for (int d = 1; d <= len / 2; ++d) {
			if (len % d) continue;

			int changeCnt = 0;
			for (int h = 0; h < d; ++h) {
				int l = h;
				int r = len - d + h;
				for (; l < r; l += d, r -= d) {
					if (s[L + l] != s[L + r]) {
						++changeCnt;
					}
				}
			}
			minChange = min(minChange, changeCnt);
		}

		return minChange;
	}
public:
	int minimumChanges(string s, int k) {
		int len = s.length();

		vector<vector<int>> semiChange(len, vector<int>(len, INT32_MAX / 4));

		for (int l = 0; l < len; ++l) {
			for (int r = l+1; r < len; ++r) {
				semiChange[l][r] = computeChange(s, l, r);
			}
		}

		vector<vector<int>> dp(len+1, vector<int>(k+1, INT32_MAX / 4));

		dp[0][0] = 0;

		for (int g = 1; g <= k; ++g) {
			for (int e = g*2; e <= len; ++e) {
				for (int sp = (g-1)*2; sp <= e-2; ++sp) {
					dp[e][g] = min(
						dp[e][g],
						dp[sp][g-1] + semiChange[sp][e-1]
					);
				}
			}
		}

		return dp[len][k];
	}
};
