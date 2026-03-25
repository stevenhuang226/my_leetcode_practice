#include "shdstd-cpp.h"

#define INF 1000000007

#include <unordered_map>
#include <map>

class Solution
{
	private:
		uint64_t encode(int32_t a, int32_t b)
		{
			return (uint64_t)(uint32_t)a << 32 | (uint64_t)(uint32_t)b;
		}
	public:
		int32_t countTrapezoids(std::vector<std::vector<int32_t>> &points)
		{
			uint32_t size = points.size();

			std::unordered_map<float, std::vector<float>> m_cutx;
			std::unordered_map<uint64_t, std::vector<float>> mid_points;

			for (int i = 0; i < size; ++i) {
				int32_t x1 = points[i][0];
				int32_t y1 = points[i][1];
				for (int i2 = i + 1; i2 < size; ++i2) {
					int32_t x2 = points[i2][0];
					int32_t y2 = points[i2][1];

					int32_t dx = x2 - x1;
					int32_t dy = y2 - y1;

					float m;
					float cx;

					if (x1 == x2) {
						m = INF;
						cx = x1;
					} else {
						m = (float)(y2 - y1) / (x2 - x1);
						cx = (float)(y1 * dx - x1 * dy) / dx;
					}
					uint64_t mid_key = encode(x1 + x2, y1 + y2);
					m_cutx[m].push_back(cx);
					mid_points[mid_key].push_back(m);
				}
			}

			int64_t ans = 0;
			for (auto &[_, mx] : m_cutx) {
				if (mx.size() <= 1) continue;

				std::map<float, int32_t> cnt;
				for (float x : mx) {
					++cnt[x];
				}

				int64_t sum = 0;
				for (auto &[_, n] : cnt) {
					ans += sum * n;
					sum += n;
				}
			}

			for (auto &[_, mps] : mid_points) {
				if (mps.size() <= 1) continue;

				std::map<float, int32_t> cnt;
				for (float m : mps) {
					++cnt[m];
				}

				int64_t sum = 0;
				for (auto &[_, n] : cnt) {
					ans -= sum * n;
					sum += n;
				}
			}

			return ans;
		}
};
