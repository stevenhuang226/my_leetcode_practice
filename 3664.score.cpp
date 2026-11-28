#include "shdstd-cpp.h"

class Solution {
public:
	int score(std::vector<std::string> &cards, char x);
};

int Solution::score(std::vector<std::string> &cards, char x) {
	using namespace std;

	vector<int> vFirst(26, 0);
	vector<int> vSecond(26, 0);

	int cx = x - 'a';

	int both, mxFreqFirst, mxFreqSecond, cntFirst, cntSecond;
	both = mxFreqFirst = mxFreqSecond = cntFirst = cntSecond = 0;

	for (const string &s : cards) {
		int c0 = s[0] - 'a';
		int c1 = s[1] - 'a';

		if (c0 == c1 && c1 == cx) {
			++both;
		} else if (c0 == cx) {
			++vFirst[c1];
			++cntFirst;
		} else if (c1 == cx) {
			++vSecond[c0];
			++cntSecond;
		}
	}

	for (int i = 0; i < 26; ++i) {
		mxFreqFirst = max(mxFreqFirst, vFirst[i]);
		mxFreqSecond = max(mxFreqSecond, vSecond[i]);
	}

	int res = 0;
	int uniqueFirst = cntFirst - mxFreqFirst;
	if (uniqueFirst < mxFreqFirst) {
		res += uniqueFirst;
		cntFirst = mxFreqFirst - uniqueFirst;
	} else {
		res += cntFirst / 2;
		cntFirst = cntFirst % 2;
	}

	int uniqueSecond = cntSecond - mxFreqSecond;
	if (uniqueSecond < mxFreqSecond) {
		res += uniqueSecond;
		cntSecond = mxFreqSecond - uniqueSecond;
	} else {
		res += cntSecond / 2;
		cntSecond = cntSecond % 2;
	}

	int reminded = min(both, cntFirst + cntSecond);
	int extra = min(res, (both - reminded) / 2);
	return res + extra + reminded;
}
