#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	string shortestBeautifulSubstring(string s, int k) {
		int left, right, best;
		left = right = 0;
		best = INT32_MAX;

		int cnt = 0;

		string res = "";

		while (left < s.length()) {
			while (right < s.length() && cnt < k) {
				cnt += (s[right++] == '1');
			}

			int len = right - left;

			if (cnt == k && len <= best) {
				string sub = s.substr(left, len);

				if (len < best) {
					res = sub;
				} else if (res > sub) {
					res = sub;
				}

				best = len;
			}

			cnt -= (s[left++] == '1');
		}

		return res;
	}
};
