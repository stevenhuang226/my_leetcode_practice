#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int stoneGameVIII(vector<int> &stones) {
		vector<int> prefix(stones.size() + 1);

		prefix[0] = 0;
		for (int i = 0; i < stones.size(); ++i) {
			prefix[i+1] = prefix[i] + stones[i];
		}

		int diff = prefix[stones.size()];
		for (int i = stones.size() - 2; i > 0; --i) {
			diff = max(diff, prefix[i+1] - diff);
		}

		return diff;
	}
};
