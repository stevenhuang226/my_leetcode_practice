#include "shdstd-cpp.h"

#define MOD 1000000007
using namespace std;

typedef struct {
	int left;
	int right;
	int mult;
} Event;

class Solution {
private:
	int64_t mod = MOD;

	int64_t fast_pow(int64_t base, int64_t e)
	{
		int64_t res = 1;
		while (e) {
			if (e & 1)
				res = (res * base) % mod;
			base = (base * base) % mod;
			e >>= 1;
		}
		return res;
	}

	int64_t inv(int64_t x)
	{
		return fast_pow(x, mod - 2);
	}
public:
	int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries)
	{
		int nums_size = nums.size();
		int split = sqrt(nums_size);

		vector<vector<Event>> events(split + 1, vector<Event>());

		for (auto &query : queries) {
			int left = query[0];
			int right = query[1];
			int step = query[2];
			int mult = query[3];

			if (step < split) {
				events[step].push_back({left, right, mult});
				continue;
			}

			for (int i = left; i <= right; i += step) {
				nums[i] = ((int64_t)nums[i] * mult) % mod;
			}
		}

		vector<int64_t> diff(nums_size + split);
		for (int sp = 1; sp < split; ++sp) {
			int sp_count = events[sp].size();

			if (sp_count == 0) continue;

			fill(diff.begin(), diff.end(), (int64_t)1);

			for (auto &ent : events[sp]) {
				int left = ent.left;
				int right =
					((ent.right - left) / sp + 1) * sp + left;
				int mult = ent.mult;

				diff[left] = (diff[left] * mult) % mod;
				diff[right] = (diff[right] * inv(mult)) % mod;
			}

			for (int i = sp; i < nums_size; ++i) {
				diff[i] = (diff[i] * diff[i-sp]) % mod;
			}
			for (int i = 0; i < nums_size; ++i) {
				nums[i] = (int32_t)(((int64_t)nums[i] * diff[i]) % mod);
			}
		}

		int res = 0;
		for (int i = 0; i < nums_size; ++i) {
			res ^= nums[i];
		}

		return res;
	}
};
