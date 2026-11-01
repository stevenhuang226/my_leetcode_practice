#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int minMoves(vector<int> &nums) {

		int minNum = INT32_MAX;
		for (int i = 0; i < nums.size(); ++i) {
			minNum = min(minNum, nums[i]);
		}

		int sum = 0;
		for (int i = 0; i < nums.size(); ++i) {
			sum += nums[i] - minNum;
		}

		return sum;
	}
};
