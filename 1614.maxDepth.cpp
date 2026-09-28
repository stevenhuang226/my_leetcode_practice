#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int maxDepth(string s) {

		int best = 0;

		int si = 0;
		for (int i = 0; i < s.length(); ++i) {
			int ch = s[i];
			if (ch == '(') {
				++si;
			} else if (ch == ')') {
				--si;
			}

			best = max(best, si);
		}

		return best;
	}
};
