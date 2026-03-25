#include "shdstd-cpp.h"

using namespace std;

class Solution {
	public:
		int minOperations(string s, int k) {
			int len = s.length();

			int zero_count = 0;
			for (auto &c : s) {
				zero_count += (c == '0');
			}

			if (zero_count == 0) {
				return 0;
			}
			if (len == k) {
				if (zero_count == len) {
					return 1;
				} else {
					return -1;
				}
			}

			if (zero_count % 2 == 1 && k % 2 == 0) {
				return -1;
			}

			int ans = INT_MAX;

			if (zero_count % 2 == 0) {
				int base = max(
						(zero_count + k - 1) / k,
						(zero_count + (len-k) - 1) / (len-k)
					      );
				base += (base % 2);

				ans = base;
			}

			if (zero_count % 2 == k % 2) {
				int base = max(
						(zero_count + k - 1) / k,
						((len-zero_count) + (len-k) - 1) / (len-k)
					      );
				base += (base % 2 == 0);
				ans = min(ans, base);
			}

			return ans;
		}
};
