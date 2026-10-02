#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int reqLen;
	int halfLen;
	vector<string> res;

	void dfs(uint16_t curr, int idx) {
		if (idx >= reqLen) {
			if (curr & (1 << reqLen))
				return;

			string r = "";
			for (int i = 0; i < reqLen; ++i) {
				if (curr & (1 << i)) {
					r += '(';
				} else {
					r += ')';
				}
			}
			res.push_back(r);
			return;
		}


		int bitCount = 0;
		for (int i = 0; i < idx; ++i) {
			if (curr & (1 << i))
				++bitCount;
		}
		int zoCount = idx - bitCount;

		if (bitCount > zoCount) {
			dfs(curr, idx+1);
		}
		if (bitCount < halfLen) {
			dfs(curr | (1 << idx), idx+1);
		}
	}
public:
	vector<string> generateParenthesis(int n) {
		halfLen = n;
		reqLen = halfLen * 2;

		dfs(0, 0);

		return res;
	}
};
