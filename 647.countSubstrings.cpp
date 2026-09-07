#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int countSubstrings(string s) {
		vector<vector<bool>> isPalindromic(s.size(), vector<bool>(s.size(), false));

		for (int i = 0; i < s.size(); ++i) {
			isPalindromic[i][i] = true;
		}

		int cnt = s.size();
		for (int l = s.size() - 1; l >= 0; --l) {
			for (int r = l + 1; r < s.size(); ++r) {
				if (s[l] != s[r])
					continue;

				if (isPalindromic[l+1][r-1] || l + 1 == r) {
					isPalindromic[l][r] = true;
					++cnt;
				}
			}
		}

		return cnt;
	}
};
