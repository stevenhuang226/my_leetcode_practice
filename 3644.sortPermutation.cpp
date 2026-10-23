#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int sortPermutation(vector<int> &nums) {
		size_t sz = nums.size();
		int res = INT32_MAX;

		int cnt = 0;
		for (int i = 0; i < sz; ++i) {
			if (nums[i] != i) {
				res &= nums[i];
				++cnt;
			}
		}

		if (cnt == 0)
			return 0;

		return res;
	}
};
