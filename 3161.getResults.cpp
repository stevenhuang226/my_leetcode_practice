#include "shdstd-cpp.h"
using namespace std;

class Solution {
	typedef struct {
		int size;
		int tree[];
	} SegmentTree;
	private:
		int exp_max = (int)(5e4+8);

		void st_update(SegmentTree *st, int curr, int curr_left, int curr_right, int target, int value)
		{
			if (curr_left == curr_right) {
				st->tree[curr] = value;
				return;
			}

			int mid = curr_left + (curr_right - curr_left) / 2;
			if (target <= mid) {
				st_update(st, curr * 2 + 1,
						curr_left, mid,
						target, value);
			} else {
				st_update(st, curr * 2 + 2,
						mid+1, curr_right,
						target, value);
			}

			st->tree[curr] = max(st->tree[curr*2+1], st->tree[curr*2+2]);
		}

		int st_query(SegmentTree *st, int curr, int curr_left, int curr_right, int query_left, int query_right) {
			if (query_right < curr_left || query_left > curr_right) {
				return -1;
			}
			if (query_left <= curr_left && query_right >= curr_right) {
				return st->tree[curr];
			}

			int mid = curr_left + (curr_right-curr_left) / 2;
			int left_max = st_query(st, curr * 2 + 1,
					curr_left, mid,
					query_left, query_right);
			int right_max = st_query(st, curr * 2 + 2,
					mid+1, curr_right,
					query_left, query_right);

			return max(left_max, right_max);
		}

	public:
		vector<bool> getResults(vector<vector<int>> &queries) {

			int count_query = 0;
			int count_obstacle = 0;

			set<int> obstacles = {0, exp_max+1};
			obstacles.insert(0);
			obstacles.insert(exp_max);

			SegmentTree *st = (SegmentTree*) calloc(1, sizeof(SegmentTree) + exp_max * 4 * sizeof(int));
			st->size = exp_max;

			vector<int> cache;
			cache.reserve(queries.size() + 2);
			for (auto &query : queries) {
				if (query[0] == 2) {
					++count_query;
					continue;
				} 
				++count_obstacle;
				int pos = query[1];
				cache.push_back(pos);
				obstacles.insert(pos);
			}
			cache.push_back(0); cache.push_back(exp_max);
			sort(cache.begin(), cache.end());
			for (int i = 1; i < cache.size(); ++i) {
				int pos = cache[i];
				int prev_pos = cache[i-1];
				st_update(st, 0, 0, exp_max, pos, pos - prev_pos);
			}

			reverse(queries.begin(), queries.end());
			vector<bool> res(count_query, false);
			int resptr = count_query;
			for (auto &query : queries) {
				if (query[0] == 2) {
					int lim = query[1];
					int sz = query[2];
					int prev_obs = *prev(obstacles.upper_bound(lim));
					int prev_gap = lim - prev_obs;
					int max_gap = st_query(st, 0, 0, exp_max, 0, lim);
					res[--resptr] = max(prev_gap, max_gap) >= sz;
					continue;
				}

				int pos = query[1];

				auto curr = obstacles.find(pos);
				int next_pos = *next(curr);
				int prev_pos = *prev(curr);

				st_update(st, 0, 0, exp_max, next_pos, next_pos - prev_pos);

				obstacles.erase(curr);
			}

			free(st);

			return res;
		}
};
