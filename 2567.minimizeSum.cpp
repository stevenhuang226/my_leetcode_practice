#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minimizeSum(vector<int> &nums) {
		int mx[3] = {0,0,0};
		int mn[3] = {INT32_MAX, INT32_MAX, INT32_MAX};

		for (int n : nums) {
			if (n > mx[0]) {
				mx[2] = mx[1];
				mx[1] = mx[0];
				mx[0] = n;
			} else if (n > mx[1]) {
				mx[2] = mx[1];
				mx[1] = n;
			} else if (n > mx[2]) {
				mx[2] = n;
			}

			if (n < mn[0]) {
				mn[2] = mn[1];
				mn[1] = mn[0];
				mn[0] = n;
			} else if (n < mn[1]) {
				mn[2] = mn[1];
				mn[1] = n;
			} else if (n < mn[2]) {
				mn[2] = n;
			}
		}

		int res = INT32_MAX;
		res = min(res, mx[2] - mn[0]);
		if (mn[1] != INT32_MAX) {
			res = min(res, mx[1] - mn[1]);
		}
		if (mn[2] != INT32_MAX) {
			res = min(res, mx[0] - mn[2]);
		}

		return res;
	}
};
