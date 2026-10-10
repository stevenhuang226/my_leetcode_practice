#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	long long minSumSquareDiff(vector<int> &nums1, vector<int> &nums2, int k1, int k2) {
		size_t sz = nums1.size();

		vector<long long> diff(sz+1);
		diff[sz] = 0;

		for (int i = 0; i < sz; ++i) {
			diff[i] = abs(nums1[i] - nums2[i]);
		}

		sort(diff.begin(), diff.end(), greater<>());

		long long ks = k1 + k2;
		for (int i = 0; i < sz; ++i) {
			long long cur = diff[i];
			long long nxt = diff[i+1];
			long long cost = (cur - nxt) * (i+1);

			if (cost <= ks) {
				ks -= cost;
				continue;
			}

			long long base = cur - ks / (i+1);
			long long rem = ks % (i+1);

			long long res = rem * (base-1) * (base-1) +
				(i+1 - rem) * base * base;

			for (int i2 = i+1; i2 < sz; ++i2) {
				res += diff[i2] * diff[i2];
			}

			return res;
		}

		return 0;
	}
};
