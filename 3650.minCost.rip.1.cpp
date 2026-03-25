#include "shdstd-cpp.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define INF32 (INT32_MAX / 4)

#define UNUSE 0
#define USED 1

class Solution {
	public:
		int minCost(int n, std::vector <std::vector <int>> &edges)
		{
			int size = edges.size();
			std::vector<std::vector<int>> dist(size, std::vector<int>(2, INF32));

			/* dist, node, state */
			std::priority_queue<
				std::tuple<int, int, int8_t>,
				std::vector<std::tuple<int, int, int8_t>,
				std::greater<>
				> mini_heap;
		}
};
