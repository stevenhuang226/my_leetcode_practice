#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int longestSubsequence(vector<int> &nums) {
		int x = 0;
		int nz_count = 0;
		for (int n : nums) {
			x ^= n;
			if (n)
				++nz_count;
		}

		if (x) {
			return nums.size();
		} else if (nz_count) {
			return nums.size() - 1;
		}
		return 0;
	}
};
