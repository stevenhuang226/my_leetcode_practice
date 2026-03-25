#include "shdstd-cpp.h"

#include <numeric>

class Solution
{
	public:
		int countPartitions(std::vector<int>& nums)
		{
			int64_t sum = std::accumulate(nums.begin(), nums.end(), 0LL);
			int size = nums.size();
			int64_t prefix = 0;
			int64_t suffix = sum;

			int32_t cnt = 0;
			for (int i = 0; i < size - 1; ++i) {
				int num = nums[i];
				prefix += num;
				suffix -= num;

				cnt += (prefix - suffix) % 2 == 0;
			}

			return cnt;
		}
};

int main()
{
	Solution solution;

	std::vector<int> nums = {10,10,3,7,6};

	int32_t res = solution.countPartitions(nums);

	std::cout << res << std::endl;

	return 0;
}
