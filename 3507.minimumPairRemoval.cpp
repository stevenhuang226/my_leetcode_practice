#include "shdstd-cpp.h"

using namespace std;

class Solution {
	public:
		int minimumPairRemoval(vector<int>& _nums) {
			int size = _nums.size();

			vector<int64_t> nums(size);
			for (int i = 0; i < size; ++i) {
				nums[i] = _nums[i];
			}

			vector<int> next_index(size);
			vector<int> prev_index(size);

			for (int i = 0; i < size; ++i) {
				next_index[i] = i + 1;
			}
			for (int i = 0; i < size; ++i) {
				prev_index[i] = i - 1;
			}

			/* sum, left_id */
			set<pair<int64_t, int>> sum_pair;

			int vilations = 0;

			for (int i = 0; i < size - 1; ++i) {
				if (nums[i] > nums[i+1]) {
					++vilations;
				}

				sum_pair.insert({nums[i] + nums[i+1], i});
			}

			int operations = 0;

			while (vilations) {
				auto min_pair = sum_pair.begin();

				int left_id = min_pair->second;
				int right_id = next_index[left_id];

				int prev_id = prev_index[left_id];
				int next_id = next_index[right_id];

				sum_pair.erase(min_pair);
				/* prev_id->left_id->right_id->next_id */

				int64_t curr_sum = nums[left_id] + nums[right_id];

				if (nums[left_id] > nums[right_id]) {
					--vilations;
				}

				if (prev_id >= 0) {
					sum_pair.erase({nums[prev_id] + nums[left_id], prev_id});
					if (nums[prev_id] > nums[left_id]) {
						--vilations;
					}
					if (nums[prev_id] > curr_sum) {
						++vilations;
					}
				}

				if (next_id < size) {
					sum_pair.erase({nums[right_id] + nums[next_id], right_id});
					if (nums[right_id] > nums[next_id]) {
						--vilations;
					}
					if (curr_sum > nums[next_id]) {
						++vilations;
					}
				}

				nums[left_id] = curr_sum;

				next_index[left_id] = next_id;
				if (next_id < size) {
					prev_index[next_id] = left_id;
				}

				++operations;

				if (prev_id >= 0) {
					sum_pair.insert({nums[prev_id] + nums[left_id], prev_id});
				}
				if (next_id < size) {
					sum_pair.insert({nums[left_id] + nums[next_id], left_id});
				}
			}

			return operations;
		}
};
