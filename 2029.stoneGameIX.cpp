#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	bool stoneGameIX(vector<int> &stones) {
		int remain[3];
		for (auto n : stones) {
			++remain[n % 3];
		}

		if (remain[0] % 2) {
			return abs(remain[1] - remain[2]) >= 3;
		} else {
			return remain[1] > 0 && remain[2] > 0;
		}
	}
};
