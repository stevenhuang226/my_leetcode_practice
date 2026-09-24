#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int smallestIndex(vector<int> &nums) {
		for (int i = 0; i < nums.size(); ++i) {
			int t = nums[i];
			int s = 0;
			while (t) {
				s += t % 10;
				t /= 10;
			}

			if (s == i) {
				return i;
			}
		}

		return -1;
	}
};
