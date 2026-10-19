#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	vector<int> targetIndices(vector<int> &nums, int target) {
		int lessCount = 0;
		int targetCount = 0;
		for (int n : nums) {
			if (n < target) {
				++lessCount;
			} else if (n == target) {
				++targetCount;
			}
		}

		vector<int> res;
		for (int i = 0; i < targetCount; ++i) {
			res.push_back(lessCount + i);
		}

		return res;
	}
};
