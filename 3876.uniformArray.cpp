#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	bool uniformArray(vector<int> &nums1) {
		int oddCnt = 0;
		int evenCnt = 0;
		int minNum = INT32_MAX;
		for (int n : nums1) {
			if (n % 2 == 0) {
				++evenCnt;
			} else {
				++oddCnt;
			}
			minNum = min(minNum, n);
		}

		if (oddCnt == 0 || evenCnt == 0)
			return true;

		if (minNum % 2 == 1)
			return true;

		return false;
	}
};
