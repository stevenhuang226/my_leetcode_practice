#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct balanceOperation {
		multiset<int> low, high;
		int64_t sumLow = 0;
		int64_t sumHigh = 0;

		void reblanace() {
			while (low.size() > high.size() + 1) {
				int x = *low.rbegin();
				low.erase(prev(low.end()));
				sumLow -= x;

				high.insert(x);
				sumHigh += x;
			}
			while (low.size() < high.size()) {
				int x = *high.begin();
				high.erase(high.begin());
				sumHigh -= x;

				low.insert(x);
				sumLow += x;
			}
		}

		void insert(int x) {
			if (low.empty() || x <= *low.rbegin()) {
				low.insert(x);
				sumLow += x;
			} else {
				high.insert(x);
				sumHigh += x;
			}
		}

		void remove(int x) {
			auto it = low.find(x);

			if (it != low.end()) {
				low.erase(it);
				sumLow -= x;
			} else {
				it = high.find(x);
				high.erase(it);
				sumHigh -= x;
			}
		}

		int64_t cost() {
			reblanace();

			int64_t m = *low.rbegin();
			return m * low.size() - sumLow +
				sumHigh - m * high.size();
		}
	};

public:
	int64_t minOperations(vector<int> &nums, int subLen, int subCnt) {
		size_t sz = nums.size();

		if ((int64_t)subLen * subCnt > sz)
			return -1;

		int64_t inf = INT64_MAX / 4;
		vector<vector<int64_t>> minOpt(subCnt+1, vector<int64_t>(sz, inf));

		balanceOperation bo;

		int r = 0;
		for (r = 0; r < subLen; ++r) {
			bo.insert(nums[r]);
		}

		for (int i = 0; i < sz; ++i) {
			minOpt[0][i] = 0;
		}
		minOpt[1][r-1] = bo.cost();

		for (; r < sz; ++r) {
			int l = r - subLen;
			bo.insert(nums[r]);
			bo.remove(nums[l]);

			int64_t cost = bo.cost();
			for (int i = subCnt; i > 0; --i) {
				minOpt[i][r] = min(
					minOpt[i][r-1],
					minOpt[i-1][l] + cost
				);
			}
		}

		return minOpt[subCnt][sz-1];
	}
};
