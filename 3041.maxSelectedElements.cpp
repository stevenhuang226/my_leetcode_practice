#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int mxNum = 1e6 + 8;
public:
	int maxSelectedElements(vector<int> &nums) {
		sort(nums.begin(), nums.end());

		int endNxt, endCur, endPrv;
		endNxt = endCur = endPrv = 0;

		int res = 0;
		int prv = 0;
		for (const int cur : nums) {
			int diff = cur - prv;

			if (diff == 1) {
				endPrv = endCur;
				endCur = endNxt;
				endNxt = 0;
			} else if (diff == 2) {
				endPrv = endNxt;
				endCur = endNxt = 0;
			} else if (diff > 2) {
				endPrv = endCur = endNxt = 0;
			}

			endNxt = max(endNxt, endCur + 1);
			endCur = max(endCur, endPrv + 1);

			res = max(res, endNxt);
			res = max(res, endCur);

			prv = cur;
		}

		return res;
	}
};
