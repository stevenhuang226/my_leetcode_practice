#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int firstStableIndex(vector<int> &nums, int k) {
		vector<int> minArr(nums.size() + 1);
		minArr[nums.size()] = INT32_MAX;

		for (int i = nums.size() - 1; i >= 0; --i) {
			minArr[i] = min(minArr[i+1], nums[i]);
		}

		int prefixMax = 0;
		for (int i = 0; i < nums.size(); ++i) {
			prefixMax = max(prefixMax, nums[i]);

			if (prefixMax - minArr[i] <= k) {
				return i;
			}
		}

		return -1;
	}
};
