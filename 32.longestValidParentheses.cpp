#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int longestValidParentheses(string s) {
		int l, r;
		int best = 0;

		l = r = 0;
		for (char c : s) {
			if (c == '(')
				++l;
			else
				++r;

			if (l == r) {
				best = max(best, r + l);
			} else if (r > l) {
				l = r = 0;
			}
		}

		l = r = 0;
		for (int i = s.length()-1; i >= 0; --i) {
			char c = s[i];

			if (c == ')')
				++r;
			else
				++l;

			if (l == r) {
				best = max(best, l + r);
			} else if (r < l) {
				l = r = 0;
			}
		}

		return best;
	}
};
