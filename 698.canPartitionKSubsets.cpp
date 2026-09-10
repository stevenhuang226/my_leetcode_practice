#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	vector<int8_t> mem;
	int targetSum;

	int8_t dfs(vector<int> &nums, uint16_t mask, int currSum) {
		if (mask == (1 << nums.size()) - 1)
			return currSum == 0;

		if (mem[mask] != -1)
			return mem[mask];

		for (int i = 0; i < nums.size(); ++i) {
			if ((1 << i) & mask)
				continue;

			if (currSum + nums[i] > targetSum)
				continue;

			int newSum = (currSum + nums[i]) % targetSum;
			if (dfs(nums, mask | (1 << i), newSum))
					return mem[mask] = 1;
		}

		return mem[mask] = 0;
	}
public:
	bool canPartitionKSubsets(vector<int> &nums, int k) {
		int sum = 0;
		for (int n : nums) {
			sum += n;
		}

		if (sum % k != 0)
			return false;

		mem = vector<int8_t>(1 << nums.size(), -1);
		targetSum = sum / k;

		return dfs(nums, 0, 0);
	}
};
