#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int sortableIntegers(vector<int> nums) {
		size_t sz = nums.size();

		int kSum = 0;
		for (int k = 1; k <= sz; ++k) {
			if (sz % k)
				continue;

			bool failed = false;
			int prevMax = 0;
			for (int base = 0; base < sz; base += k) {
				int mx = 0;
				int mn = INT32_MAX;

				int len = 0;
				int mxLen = 0;
				for (int i = 0; i < (k * 2) - 1; ++i) {
					int cur = base + i % k;
					int nxt = base + (i+1) % k;
					mx = max(mx, nums[cur]);
					mn = min(mn, nums[cur]);

					if (nums[cur] <= nums[nxt]) {
						++len;
					} else {
						len = 0;
					}
					mxLen = max(mxLen, len);
				}

				if (mn < prevMax || mxLen < k-1) {
					failed = true;
					break;
				}

				prevMax = mx;
			}

			if (!failed) {
				kSum += k;
			}
		}

		return kSum;
	}
};
