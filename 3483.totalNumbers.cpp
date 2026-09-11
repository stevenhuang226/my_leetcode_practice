#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int totalNumbers(vector<int> &digit) {
		vector<bool> mrk(1000, false);

		int cnt = 0;
		for (int i = 0; i < digit.size(); ++i) {
			for (int i2 = 0; i2 < digit.size(); ++i2) {
				for (int i3 = 0; i3 < digit.size(); ++i3) {
					if (i == i2 || i2 == i3 || i == i3)
						continue;
					if (digit[i] == 0)
						continue;

					int num = digit[i]*100 + digit[i2]*10 + digit[i3];
					if (mrk[num])
						continue;

					if (num % 2 == 1)
						continue;

					mrk[num] = true;
					++cnt;
				}
			}
		}

		return cnt;
	}
};
