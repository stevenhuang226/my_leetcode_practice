#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minMoves(vector<int> &nums) {
		int mx = 0;

		for (const int &n : nums) {
			mx = max(mx, n);
		}

		int sum = 0;
		for (const int &n : nums) {
			sum += mx - n;
		}

		return sum;
	}
};
