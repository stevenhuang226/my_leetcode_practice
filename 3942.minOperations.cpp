#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minOperations(vector<int> &nums) {
		size_t sz = nums.size();

		int zeroPos = sz-1;
		int gapCnt = 0;

		for (int i = 0; i < sz; ++i) {
			int cur = nums[i];
			int nxt = nums[(i+1)%sz];
			if (abs(nxt - cur) > 1) {
				++gapCnt;
			}
			if (cur == 0) {
				zeroPos = i;
			}
		}

		if (gapCnt > 1)
			return -1;

		if (sz <= 2 && nums[0] == 0)
			return 0;

		if (nums[(zeroPos+1)%sz] == sz-1) {
			return min(zeroPos + 1,
			(int)sz-zeroPos - 1) + 1;
		}
		return min(zeroPos, (int)sz-zeroPos+2);
	}
};
