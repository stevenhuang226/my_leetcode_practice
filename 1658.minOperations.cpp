#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minOperations(vector<int> &nums, int x) {
		int sum = 0;
		for (int n : nums) {
			sum += n;
		}


		int r = 0;
		int best = INT32_MAX;
		for (int l = -1; l < (int)nums.size(); ++l) {
			if (l >= 0) {
				sum += nums[l];
			}

			while (r <= l || (r < nums.size() && sum > x)) {
				sum -= nums[r++];
			}

			if (sum == x) {
				int opt = l + (nums.size() - r) + 1;
				best = min(best, opt);
			}
		}

		if (best == INT32_MAX)
			return -1;

		return best;
	}
};
