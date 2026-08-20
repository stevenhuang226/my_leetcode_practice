#include "shdstd-cpp.h"

using namespace std;

class Solution{
public:
	vector<int> resultArray(vector<int> &nums) {
		vector<int> res;
		vector<int> bfr;

		res.push_back(nums[0]);
		bfr.push_back(nums[1]);

		for (int i = 2; i < nums.size(); ++i) {
			int curr = nums[i];

			if (res[res.size()-1] > bfr[bfr.size()-1]) {
				res.push_back(curr);
			} else {
				bfr.push_back(curr);
			}
		}

		for (int i = 0; i < bfr.size(); ++i) {
			res.push_back(bfr[i]);
		}

		return res;
	}
};
