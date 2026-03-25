#include "shdstd-cpp.h"

class Solution {
	public:
		std::vector<int> countBits(int n)
		{
			std::vector<int32_t> ret(n+1);

			ret[0] = 0;

			for (int i = 1; i <= n; ++i) {
				ret[i] = ret[i >> 1] + (i & 1);
			}

			return ret;
		}
};
