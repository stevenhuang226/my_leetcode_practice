#include "shdstd-cpp.h"

class Solution
{
	public:
		bool canJump(std::vector<int>& nums)
		{
			int32_t size = nums.size();
			if (size <= 1) {
				return true;
			}
			int32_t max_range = nums[0];
			for (int i = 0; i < max_range; ++i) {
				max_range = std::max(max_range, (i+1) + nums[i]);
				if (max_range >= size) {
					return true;
				}
			}

			return false;
		}
};

int main()
{
	Solution solution;

	std::vector<int> nums = {2,3,1,1,4};
	bool res = solution.canJump(nums);

	std::cout << res << std::endl;

	return 0;
}
