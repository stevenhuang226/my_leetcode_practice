#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int maxPalindromes(string s, int k) {
		int sz = s.length();

		vector<vector<bool>> isPal(sz, vector<bool>(sz, false));
		for (int i = 0; i < sz; ++i) {
			isPal[i][i] = true;
		}

		for (int l = sz-2; l >= 0; --l) {
			for (int r = l+1; r < sz; ++r) {
				if (s[l] != s[r])
					continue;

				if (l + 1 == r) {
					isPal[l][r] = true;
				} else {
					isPal[l][r] = isPal[l+1][r-1];
				}
			}
		}

		vector<int> maxCount(sz+1, 0);
		int best = 0;

		for (int i = 1; i <= sz; ++i) {
			maxCount[i] = maxCount[i-1];
			int r = i-1;
			for (int l = 0; l <= i - k; ++l) {
				if (isPal[l][r]) {
					maxCount[i] = max(maxCount[i], maxCount[l] + 1);
				}
			}
			best = max(best, maxCount[i]);
		}

		return best;
	}
};
