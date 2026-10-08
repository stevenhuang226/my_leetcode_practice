#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	string removeOuterParentheses(string s) {
		int st = 0;
		string res = "";

		for (char c : s) {
			if (c == '(') {
				++st;
			}

			if (st != 1) {
				res.push_back(c);
			}

			if (c == ')') {
				--st;
			}
		}

		return res;
	}
};
