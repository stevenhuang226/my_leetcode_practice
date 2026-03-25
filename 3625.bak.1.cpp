#include "shdstd-cpp.h"

#include <unordered_map>

#define C2(x) ((x) * ((x) - 1) / 2)

typedef struct {
	int a;
	int b;
	int c;

	int p1x;
	int p1y;

	int p2x;
	int p2y;
} Line;

class Solution
{
	private:
		uint64_t encode(int32_t a, int32_t b)
		{
			return (uint64_t)(uint32_t)a << 32 | (uint64_t)(uint32_t)b;
		}
	public:
		int countTrapezoids(std::vector<std::vector<int>>& points)
		{
			int size = points.size();
			Line *lines = (Line *)malloc(size * size * sizeof(Line));

			uint32_t lp = 0;

			for (int i = 0; i < size; ++i) {
				int p1x = points[i][0];
				int p1y = points[i][1];
				for (int i2 = i + 1; i2 < size; ++i2) {

					int p2x = points[i2][0];
					int p2y = points[i2][1];

					int dx = p1x - p2x;
					int dy = p1y - p2y;
					
					int g = std::gcd(abs(dx), abs(dy));
					dx /= g;
					dy /= g;

					if (dx < 0 || (dx == 0) && dy < 0) {
						dx = -dx;
						dy = -dy;
					}

					lines[lp].a = dy;
					lines[lp].b = -dx;
					lines[lp].c = dx*p1y - dy*p1x;
					lines[lp].p1x = p1x;
					lines[lp].p1y = p1y;
					lines[lp].p2x = p2x;
					lines[lp].p2y = p2y;

					++lp;
				}
			}

			std::unordered_map<uint64_t, std::vector<Line *>> mp;
			mp.reserve(lp);

			for (int i = 0; i < lp; ++i) {
				int dx = lines[i].dx;
				int dy = lines[i].dy;
				uint64_t key = encode(dx, dy);
				mp[key].push_back(&(lines[i]));
			}

			uint32_t ans = 0;

			for (auto &e : mp) {
				std::unordered_map<uint64_t, uint32_t> deg;

				auto &val = e.second;

				uint32_t cnt = 0;
				for (Line *ln : val) {
					++cnt;
					int p1x = ln->p1x;
					int p1y = ln->p1y;
					uint64_t key1 = encode(p1x, p1y);
					int p2x = ln->p2x;
					int p2y = ln->p2y;
					uint64_t key2 = encode(p2x, p2y);
					++deg[key1];
					++deg[key2];
				}

				uint32_t paris = C2(cnt);

				uint32_t no_vaild = 0;
				for (auto &d : deg) {
					uint32_t t = d.second;
					if (t < 2) continue;

					no_vaild += C2(t);
				}

				ans += (paris - no_vaild);
			}

			free(lines);

			return ans;
		}
};
