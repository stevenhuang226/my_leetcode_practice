#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	string parentheses;

	int exp(int base, int e) {
		int res = 1;
		while (e) {
			if (e & 1) {
				res = res * base;
			}

			e >>= 1;
			base = base * base;
		}
		return res;
	}

	int dfs(int l, int r) {
		if (l == r) {
			return 0;
		}
		if (r - l + 1 == 2) {
			return 1;
		}

		int st = 0;
		int f;
		for (f = l; f <= r; ++f) {
			if (parentheses[f] == '(') {
				++st;
			}
			if (parentheses[f] == ')') {
				--st;
			}

			if (st == 0)
				break;
		}

		if (f != r) {
			return dfs(l, f) + dfs(f+1, r);
		}
		return 2 * dfs(l+1, r-1);
	}

public:
	int scoreOfParentheses(string s) {
		parentheses = s;

		return dfs(0, s.length()-1);
	}
};
