#include "shdstd-cpp.h"

class Solution
{
	public:
		int maxSubArray(std::vector<int>& nums)
		{
			int32_t prefix = 0;
			int32_t maximum = INT_MIN;
			int32_t size = nums.size();

			for (int i = 0; i < size; ++i) {
				prefix += nums[i];
				maximum = std::max(maximum, prefix);
				prefix = std::max(0, prefix);
			}
			return maximum;
		}
};
