#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	bool canAliceWin(int n) {
		int s = 10;
		for (;;) {
			n -= s;
			--s;

			if (n < 0) {
				return s % 2 == 0;
			}
		}
	}
};
