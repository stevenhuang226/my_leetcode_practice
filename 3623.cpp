#include "shdstd-cpp.h"
#include <unordered_map>

#define MOD 1000000007

class Solution
{
public:
	int32_t countTrapezoids(std::vector<std::vector<int>>& points)
	{
		std::unordered_map<int32_t, uint32_t>hor_pos_cnt;

		uint32_t size = points.size();

		for (int i = 0; i < size; ++i) {
			int y = points[i][1];
			++hor_pos_cnt[y];
		}

		uint64_t cnt = 0;
		uint64_t combos = 0;
		for (auto &item : hor_pos_cnt) {
			if (item.second < 2) {
				continue;
			}
			uint64_t x = item.second;
			uint64_t curr = x * (x - 1) / 2;
			uint64_t new_combo = (curr * combos) % MOD;
			cnt = (cnt + new_combo) % MOD;
			combos = (combos + curr) % MOD;
		}

		return (int32_t)(cnt % MOD);
	}
};
