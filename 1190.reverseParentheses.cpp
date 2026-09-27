#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	string reverseParentheses(string s) {
		vector<int> match(s.length(), -1);
		stack<int> st;

		for (int i = 0; i < s.length(); ++i) {
			if (s[i] == '(') {
				st.push(i);
			} else if (s[i] == ')') {
				match[st.top()] = i;
				match[i] = st.top();
				st.pop();
			}
		}

		string res = "";
		int adj = 1;
		int i = 0;
		while (i != s.length()) {
			if (match[i] != -1) {
				i = match[i];
				adj = -adj;
			} else {
				res += s[i];
			}
			i += adj;
		}

		return res;
	}
};
