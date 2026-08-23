#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	bool sumGame(string num) {
		int len = num.length();

		int leftQ, rightQ, leftSum, rightSum;
		leftQ = rightQ = leftSum = rightSum = 0;

		for (int i = 0; i < len / 2; ++i) {
			if (num[i] == '?') {
				++leftQ;
			} else {
				leftSum += num[i] - '0';
			}
		}
		for (int i = len / 2; i < len; ++i) {
			if (num[i] == '?') {
				++rightQ;
			} else {
				rightSum += num[i] - '0';
			}
		}

		if (leftQ > rightQ && leftSum > rightSum) {
			return true;
		}
		if (rightQ > leftQ && rightSum > leftSum) {
			return true;
		}

		int diffSum = abs(leftSum - rightSum);
		int diffQ = abs(leftQ - rightQ);

		if ((diffQ % 2 == 0) && diffSum == ((diffQ / 2) * 9)) {
			return false;
		}

		return true;
	}
};
