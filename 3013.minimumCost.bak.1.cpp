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

			for (int i = 1; i <= dist; ++i) {
				remained.insert(nums[i]);
			}

			int arr_lim = size - max(subs, dist);

			for (int left = 1; left < arr_lim; ++left) {
				int right_num = nums[left+dist];
				int left_num = nums[left];

				if (! mini_set.empty() && right_num <= *prev(mini_set.end())) {
					mini_set.insert(right_num);
					mini_set_sum += right_num;
				} else {
					remained.insert(right_num);
				}

				while (mini_set.size() > subs - 1) {
					auto it = prev(mini_set.end());
					mini_set_sum -= *it;
					remained.insert(*it);
					mini_set.erase(it);
				}

				while (mini_set.size() < subs - 1) {
					auto it = remained.begin();
					mini_set_sum += *it;
					mini_set.insert(*it);
					remained.erase(it);
				}

				auto it_left_num = mini_set.find(left_num);
				if (it_left_num != mini_set.end()) {
					mini_set_sum -= left_num;
					mini_set.erase(it_left_num);
				} else {
					remained.erase(remained.find(left_num));
				}

				min_cost = min(min_cost, nums[0] + mini_set_sum);
			}

			return min_cost;
		}
};
