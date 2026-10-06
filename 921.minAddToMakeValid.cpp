#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minAddToMakeValid(string s) {
		int st = 0;

		int addCount = 0;
		for (char c : s) {
			if (c == '(') {
				++st;
			} else {
				--st;
			}

			if (st < 0) {
				st = 0;
				++addCount;
			}
		}

		addCount += st;

		return addCount;
	}
};
