#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	vector<vector<bool>> isPalindrome;
	vector<vector<string>> res;
	vector<string> route;

	void dfs(const string &s, int left) {
		if (left == s.length()) {
			res.push_back(route);
			return;
		}

		for (int right = left; right < s.length(); ++right) {
			if (! isPalindrome[left][right])
				continue;

			route.push_back(s.substr(left, right-left+1));

			dfs(s, right+1);

			route.pop_back();
		}
	}
public:
	vector<vector<string>> partition(string s) {
		size_t len = s.length();

		isPalindrome.resize(len, vector<bool>(len, false));

		for (int l = len-1; l >= 0; --l) {
			isPalindrome[l][l] = true;
			for (int r = l+1; r < len; ++r) {
				isPalindrome[l][r] =
					(s[l] == s[r]) &&
					(r-l <= 2 || isPalindrome[l+1][r-1]);
			}
		}

		dfs(s, 0);

		return res;
	}
};
