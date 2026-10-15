#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int mod = 1e9 + 7;
public:
	int sumCounts(vector<int> &nums) {
		int64_t sum = 0;
		int64_t res = 0;

		vector<int> last((int)1e2 + 8, -1);
		vector<int> distinct(nums.size(), 0);

		for (int i = 0; i < nums.size(); ++i) {
			int mid = last[nums[i]];

			int rangeSum = 0;
			for (int i2 = mid + 1; i2 <= i; ++i2) {
				rangeSum += distinct[i2];
				++distinct[i2];
			}

			sum = sum + (2 * rangeSum) + (i - mid);

			last[nums[i]] = i;

			res += sum;
		}

		return res;
	}
};
