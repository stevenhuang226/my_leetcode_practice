#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int missingMultiple(vector<int> &nums, int k) {
		sort(nums.begin(), nums.end());

		int m = k;
		int p = 0;
		while (p < nums.size()) {
			while (p < nums.size() && nums[p] < m) {
				++p;
			}

			if (p >= nums.size() || nums[p] != m) {
				return m;
			}

			m += k;
		}

		return m;
	}
};
