#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int longestMonotonicSubarray(vector<int> &nums) {
		if (nums.size() == 0)
			return 0;

		int inc, des, mx;

		inc = des = mx = 1;

		for (size_t i = 1; i < nums.size(); ++i) {
			int prv = nums[i-1];
			int cur = nums[i];

			if (cur > prv) {
				++inc;
			} else {
				inc = 1;
			}

			if (cur < prv) {
				++des;
			} else {
				des = 1;
			}

			mx = max(mx, inc);
			mx = max(mx, des);
		}

		return mx;
	}
};
