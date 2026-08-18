#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int largestInteger(vector<int> &nums, int k) {
		int freq[58] = {0};
		for (auto n : nums) {
			++freq[n];
		}

		if (k == nums.size()) {
			for (int i = 57; i >= 0; --i) {
				if (freq[i]) {
					return i;
				}
			}
		}

		if (k == 1) {
			for (int i = 57; i >= 0; --i) {
				if (freq[i] == 1) {
					return i;
				}
			}
		}

		int start = nums[0];
		int end = nums[nums.size()-1];

		if ((start+1) * (freq[start] == 1) > (end+1) * (freq[end] == 1)) {
			return start;
		} else if ((end+1) * (freq[end] == 1) > (start+1) * (freq[start] == 1)) {
			return end;
		}
		return -1;
	}
};
