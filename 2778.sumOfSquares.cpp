#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int sumOfSquares(vector<int> &nums) {
		size_t sz = nums.size();

		int sum = 0;
		for (int i = 0; i < sz; ++i) {
			if (sz % (i+1) == 0) {
				sum += nums[i] * nums[i];
			}
		}

		return sum;
	}
};
