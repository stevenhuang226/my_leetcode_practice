#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct segment {
		int64_t val;
		int cnt;
	};
public:
	int64_t countNonDecreasingSubarrays(vector<int> &nums, int limit) {
		deque<segment> dq;

		int64_t cost = 0;
		int64_t res = 0;

		int R = nums.size() - 1;
		for (int L = nums.size() - 1; L >= 0; --L) {
			int64_t num = nums[L];
			int cnt = 1;

			while (!dq.empty() && dq.back().val < num) {
				segment curr = dq.back();
				dq.pop_back();

				cnt += curr.cnt;
				cost += (num - curr.val) * curr.cnt;
			}
			dq.push_back({num, cnt});

			while (cost > limit) {
				segment curr = dq.front();
				dq.pop_front();

				cost -= curr.val - nums[R--];
				if (curr.cnt > 1) {
					dq.push_front({curr.val, curr.cnt-1});
				}
			}

			res += R - L + 1;
		}

		return res;
	}
};
