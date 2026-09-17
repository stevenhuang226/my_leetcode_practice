#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int inf32 = INT32_MAX / 4;
public:
	int minSumOfLengths(vector<int> &arr, int target) {
		vector<int> best(arr.size() + 1, inf32);
		int best_sum = inf32;

		int l = 0;
		int curr = 0;
		for (int r = 0; r < arr.size(); ++r) {
			curr += arr[r];
			while (l < r && curr > target) {
				curr -= arr[l++];
			}

			best[r+1] = best[r];

			if (curr != target)
				continue;

			int len = r - l + 1;
			best_sum = min(best_sum, best[l] + len);
			best[r+1] = min(best[r+1], len);
		}

		if (best_sum >= inf32) {
			return -1;
		}
		return best_sum;
	}
};
