#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int64_t mod = 1e9 + 7;
public:
	int distinctSubseqII(string s) {

		int64_t dp = 1;
		vector<int> last(26, 0);

		for (int i = 0; i < s.length(); ++i) {
			int ch = s[i] - 'a';

			int64_t p = dp;
			dp = (dp * 2 - last[ch]) % mod;
			last[ch] = p;
		}

		return (dp + mod - 1) % mod;
	}
};
