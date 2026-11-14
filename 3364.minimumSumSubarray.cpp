#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minimumSumSubarray(vector<int> &nums, int mn, int mx) {
		int res = INT32_MAX;

		size_t size = nums.size();

		vector<int> prefix(size+1);
		prefix[0] = 0;
		for (size_t i = 0; i < size; ++i) {
			prefix[i+1] = prefix[i] + nums[i];
		}

		for (size_t i = 0; i < size; ++i) {
			for (size_t i2 = mn-1; i+i2 < size && i2 < mx; ++i2) {
				int sum = prefix[i+i2+1] - prefix[i];
				if (sum <= 0) continue;
				res = min(res, sum);
			}
		}

		if (res == INT32_MAX)
			return -1;

		return res;
	}
};
