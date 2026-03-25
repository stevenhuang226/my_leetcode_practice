#include "shdstd-cpp.h"
#include <vector>

class Solution
{
	public:
		int32_t countCollisions(std::string directions)
		{
			uint32_t size = directions.size();

			uint32_t collisions = 0;

			uint32_t rights = 0;
			uint32_t lefts = 0;

			for (int i = 0; i < size; ++i) {
				if (directions[i] == 'R') {
					++rights;
					continue;
				}
				collisions += rights;
				rights = 0;
			}

			for (int i = size - 1; i >= 0; --i) {
				if (directions[i] == 'L') {
					++lefts;
					continue;
				}
				collisions += lefts;
				lefts = 0;
			}

			return (int32_t)collisions;
		}
};
