#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minOperations(string s) {
		size_t len = s.length();
		char mn = s[len-1];
		char mx = s[len-1];

		bool eqht = false;

		int des = 0;
		for (int i = 0; i < len-1; ++i) {
			char cur = s[i];
			char nxt = s[i+1];
			if (cur > nxt)
				++des;

			mn = min(mn, cur);
			mx = max(mx, cur);

			if (i >= 1 && cur == s[0] || cur == s[len-1])
				eqht = true;
		}

		if (des == 0)
			return 0;
		if (len == 2)
			return -1;

		if (s[0] == mn || s[len-1] == mx)
			return 1;
		if (s[0] == mx && s[len-1] == mn && !eqht) {
			return 3;
		}
		return 2;
	}
};
