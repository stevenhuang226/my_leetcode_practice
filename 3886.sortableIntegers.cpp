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

				int desCnt = 0;
				for (int i = 0; i < k; ++i) {
					int cur = base + i % k;
					int nxt = base + (i+1) % k;
					mx = max(mx, nums[cur]);
					if (prevMax > nums[cur]) {
						failed = true;
						break;
					}

					if (nums[cur] > nums[nxt]) {
						++desCnt;
					}
				}

				if (desCnt > 1) {
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
