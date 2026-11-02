#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minMoves2(vector<int> &nums) {
		sort(nums.begin(), nums.end());

		int half = nums[nums.size() / 2];
		int sum = 0;
		for (const int &n : nums) {
			sum += abs(n - half);
		}
		return sum;
	}
};
