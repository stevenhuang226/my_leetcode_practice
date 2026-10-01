#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	bool isValid(string s) {

		stack<char> st;

		for (int i = 0; i < s.length(); ++i) {
			char c = s[i];
			switch (c) {
				case '(':
				case '[':
				case '{':
					st.push(c);
					st.push(c);
					break;
				case ')':
					if (st.empty() || st.top() != '(')
						return false;
					break;
				case ']':
					if (st.empty() || st.top() != '[')
						return false;
					break;
				case '}':
					if (st.empty() || st.top() != '{')
						return false;
					break;
			}
			st.pop();
		}

		return st.empty();
	}
};
