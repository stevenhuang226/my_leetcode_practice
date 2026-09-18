#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct Range {
		int start;
		int end;
	};

public:
	vector<string> maxNumOfSubstrings(string s) {
		vector<int> firstPos(26, -1);
		vector<int> lastPos(26, 0);
		for (int i = 0; i < s.length(); ++i) {
			int c = s[i] - 'a';
			if (firstPos[c] < 0) {
				firstPos[c] = i;
			}
			lastPos[c] = i;
		}

		vector<Range> rgs;
		for (int i = 0; i < 26; ++i) {
			int l = firstPos[i];
			int r = lastPos[i];
			int8_t brk = false;
			for (int i2 = l+1; i2 < r; ++i2) {
				int c = s[i2] - 'a';

				r = max(r, lastPos[c]);

				if (firstPos[c] < l) {
					brk = true;
					break;
				}
			}

			if (!brk)
				rgs.push_back({l, r});
		}

		sort(rgs.begin(), rgs.end(), [](const Range &a, const Range &b) {
			if (a.end != b.end) {
				return a.end < b.end;
			}
			return a.start > b.start;
		});

		vector<string> res;
		int ed = -1;
		for (int i = 0; i < rgs.size(); ++i) {
			if (rgs[i].start <= ed)
				continue;

			res.push_back(s.substr(rgs[i].start, rgs[i].end - rgs[i].start + 1));
			ed = rgs[i].end;
		}

		return res;
	}
};
