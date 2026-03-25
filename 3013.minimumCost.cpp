#include "shdstd-cpp.h"

using namespace std;

#define INF64 (INT64_MAX / 4)
class Solution {
	public:
		int64_t minimumCost(vector<int> &nums, int subs, int dist) {
			int size = nums.size();

			int64_t mini_set_sum = 0;
			multiset<int64_t> mini_set;
			multiset<int64_t> remained;

			int64_t min_cost = INF64;

			for (int i = 1; i <= dist + 1; ++i) {
				int num = nums[i];

				mini_set_sum += num;
				mini_set.insert(num);

				while (mini_set.size() > subs - 1) {
					auto it = prev(mini_set.end());
					mini_set_sum -= *it;
					remained.insert(*it);
					mini_set.erase(it);
				}
			}

			if (mini_set.size() == subs - 1) {
				min_cost = mini_set_sum + nums[0];
			}

			for (int left = 1; left < size - dist - 1; ++left) {
				int left_num = nums[left];
				int right_num = nums[left + dist + 1];

				if (! mini_set.empty() && right_num > *prev(mini_set.end())) {
					remained.insert(right_num);
				} else {
					mini_set_sum += right_num;
					mini_set.insert(right_num);
				}

				auto it_left = mini_set.find(left_num);
				if (it_left != mini_set.end()) {
					mini_set_sum -= left_num;
					mini_set.erase(it_left);
				} else {
					remained.erase(remained.find(left_num));
				}

				while (mini_set.size() > subs - 1) {
					auto it = prev(mini_set.end());
					remained.insert(*it);
					mini_set_sum -= *it;
					mini_set.erase(it);
				}
				while (mini_set.size() < subs - 1) {
					auto it = remained.begin();
					mini_set_sum += *it;
					mini_set.insert(*it);
					remained.erase(it);
				}

				min_cost = min(min_cost, nums[0] + mini_set_sum);
			}

			return min_cost;
		}
};
