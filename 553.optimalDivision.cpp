#include "shdstd-cpp.h"

using namespace std;
class Solution {
public:
	string optimalDivision(vector<int> &nums) {
		string res = to_string(nums[0]);

		if (nums.size() == 1) {
			return res;
		}

		res += "/";

		if (nums.size() >= 3)
			res += "(";

		for (ssize_t i = 1; i < nums.size(); ++i) {
			if (i != 1)
				res += "/";
			
			res += to_string(nums[i]);
		}

		if (nums.size() >= 3)
			res += ")";

		return res;
	}
};
