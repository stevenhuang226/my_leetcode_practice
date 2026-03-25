#include "shdstd-cpp.h"
#include <algorithm>
#include <numeric>

class Solution {
	public:
		int64_t maxRunTime(int n, std::vector<int>& batteries) {
			std::sort(batteries.begin(), batteries.end(), std::greater<int>());
			
			int64_t sum = std::accumulate(batteries.begin(), batteries.end(), 0LL);

			for (auto &i : batteries) {
				if (i <= sum / n) {
					break;
				}

				sum -= i;
				n--;
			}

			return sum / n;
		}
};
