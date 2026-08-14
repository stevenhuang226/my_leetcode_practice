#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int maximumLengthSubstring(string s) {
		int best = 0;

		int freq[26] = {0};

		int right = 0;
		for (int left = 0; left < s.size(); ++left) {
			while (right < s.size() && freq[s[right] - 'a'] <= 1) {
				++freq[s[right++] - 'a'];
			}
			best = max(best, right - left);
			--freq[s[left] - 'a'];
		}

		return best;
	}
};
