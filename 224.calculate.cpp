#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int calculate(string s) {
		int invert = 1;
		int64_t res = 0;

		stack<bool> st;

		int64_t tmp;
		int negative = 1;
		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == ' ' || s[i] == '+')
				continue;

			if (s[i] == '-') {
				negative = -1;
				continue;
			}

			if (s[i] == '(') {
				if (negative < 0) {
					invert = -invert;
					negative = 1;
					st.push(true);
				} else {
					st.push(false);
				}
				continue;
			} else if (s[i] == ')') {
				if (st.top()) {
					invert = -invert;
				}
				st.pop();
				continue;
			}

			tmp = 0;
			while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
				tmp = tmp * 10 + s[i++] - '0';
			}
			--i;

			res += tmp * invert * negative;

			negative = 1;
		}

		return res;
	}
};
