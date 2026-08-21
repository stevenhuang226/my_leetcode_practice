#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int64_t findKthSmallest(vector<int> &coins, int k) {
		int64_t left = 0;
		int64_t right = (int64_t)1e11;

		int sz = coins.size();

		while (left < right) {
			int64_t mid = left + (right - left) / 2;

			int64_t cnt = 0;
			for (int mask = 1; mask < (1 << sz); ++mask) {
				int64_t l = 1;
				for (int i = 0; i < sz; ++i) {
					if (! (mask & (1 << i)))
						continue;

					l = lcm(l, coins[i]);
					if (l > mid) {
						break;
					}
				}
				if (l > mid)
					continue;

				int64_t multiples = mid / l;
				if (__builtin_popcount(mask) & 1) {
					cnt += multiples;
				} else {
					cnt -= multiples;
				}
			}

			if (cnt >= k) {
				right = mid;
			} else {
				left = mid + 1;
			}
		}

		return left;
	}
};
