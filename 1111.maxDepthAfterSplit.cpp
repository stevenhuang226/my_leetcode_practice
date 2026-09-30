#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	vector<int> maxDepthAfterSplit(string sq) {
		vector<int> res(sq.length(), 0);

		int st = 0;
		int maxDepth = 0;
		for (char c : sq) {
			if (c == '(') {
				++st;
			} else {
				--st;
			}

			maxDepth = max(maxDepth, st);
		}

		st = 0;
		int halfDepth = maxDepth / 2;
		for (int i = 0; i < sq.length(); ++i) {
			char c = sq[i];

			if (c == '(') {
				++st;
			} 
			if (st > halfDepth) {
				res[i] = 1;
			}
			if (c == ')') {
				--st;
			}
		}

		return res;
	}
};
