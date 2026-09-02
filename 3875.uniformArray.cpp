#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	bool uniformArray(vector<int> &nums) {
		if (nums.size() == 1)
			return true;

		bool even, odd;
		even = odd = true;

		for (int i = 0; i < nums.size(); ++i) {

			bool lEven = false;
			bool lOdd = false;
			for (int i2 = 0; i2 < nums.size(); ++i2) {
				if (i == i2)
					continue;
				int s = nums[i] - nums[i2];
				if (s % 2 == 0) {
					lEven = true;
				} else {
					lOdd = true;
				}
			}

			if (!lEven)
				even = false;

			if (!lOdd)
				odd = false;
		}

		return even || odd;
	}
};
