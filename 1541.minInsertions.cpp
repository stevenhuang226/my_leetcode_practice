#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minInsertions(string s) {
		int balance = 0;
		int cnt = 0;

		for (char curr : s) {
			if (curr == '(') {
				balance += 2;

				if (balance & 1) {
					++cnt;
					--balance;
				}
			} else {
				--balance;

				if (balance < 0) {
					++cnt;
					balance += 2;
				}
			}
		}

		return cnt + balance;
	}
};
