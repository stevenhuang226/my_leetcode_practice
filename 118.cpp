#include "shdstd-cpp.h"

class Solution
{
	public:
		std::vector<std::vector<int>> generate(int num_rows)
		{
			std::vector<std::vector<int32_t>> triangle;
			triangle.reserve(num_rows);

			for (int i = 0; i < num_rows; ++i) {
				std::vector<int32_t> row(i + 1);
				row[0] = 1;
				row[i] = 1;
				for (int i2 = 1; i2 < i; ++i2) {
					row[i2] = triangle[i - 1][i2 - 1] + triangle[i - 1][i2];
				}

				triangle.push_back(row);
			}

			return triangle;
		}
};
