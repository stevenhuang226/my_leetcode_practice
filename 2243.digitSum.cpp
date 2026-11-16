#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	string digitSum(string s, int k) {
		string newStr = "";
		while (s.length() > k) {
			for (int i = 0; i < s.length(); i += k) {
				int len = min(k, (int)s.length() - i);
				string sub = s.substr(i, len);

				int subSum = 0;
				for (const char c : sub) {
					subSum += c - '0';
				}

				if (!subSum) {
					newStr += '0';
				}
				sub = "";
				while (subSum) {
					sub += (subSum % 10) + '0';
					subSum /= 10;
				}

				reverse(sub.begin(), sub.end());
				newStr += sub;
			}

			s = newStr;
			newStr = "";
		}

		return s;
	}
};
