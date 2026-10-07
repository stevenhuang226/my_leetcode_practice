#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	set<string> resSet;

	void minDeletion(const string &s, int &lR, int &rR) {
		int st = 0;
		for (char c : s) {
			if (c == '(') {
				++st;
			} else if (c == ')') {
				--st;
			}

			if (st < 0) {
				st = 0;
				++rR;
			}
		}
		lR = st;
	}

	void dfs(const string &s, int idx, int st, int lR, int rR, string &curr) {
		if (idx == s.length()) {
			if (st == 0 &&
			lR == 0 &&
			rR == 0) {
				resSet.insert(curr);
			}
			return;
		}

		char c = s[idx];

		if (c == '(') {
			if (lR > 0) {
				dfs(s, idx+1, st, lR - 1, rR, curr);
			}

			curr.push_back(c);
			dfs(s, idx+1, st+1, lR, rR, curr);
			curr.pop_back();
		} else if (c == ')') {
			if (rR > 0)
				dfs(s, idx+1, st, lR, rR - 1, curr);

			if (st > 0) {
				curr.push_back(c);
				dfs(s, idx+1, st-1, lR, rR, curr);
				curr.pop_back();
			}
		} else {
			curr.push_back(c);
			dfs(s, idx+1, st, lR, rR, curr);
			curr.pop_back();
		}
	}
public:
	vector<string> removeInvalidParentheses(string s) {
		int lR, rR;
		lR = rR = 0;
		minDeletion(s, lR, rR);

		string curr = "";

		dfs(s, 0, 0, lR, rR, curr);

		return vector<string>(resSet.begin(), resSet.end());
	}
};
