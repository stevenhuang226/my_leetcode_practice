#include "shdstd-cpp.h"

class Solution
{
	public:
		std::vector<int32_t> getRow(int row_index)
		{
			int32_t *last = (int32_t *)calloc((row_index + 1), sizeof(int32_t));
			int32_t *curr = (int32_t *)malloc((row_index + 1) * sizeof(int32_t));
			for (int i = 0; i <= row_index; ++i) {
				curr[0] = 1;
				curr[i] = 1;
				for (int i2 = 1; i2 < i; ++i2) {
					curr[i2] = last[i2-1] + last[i2];
				}
				int32_t *tmp = last;
				last = curr;
				curr = tmp;
			}

			std::vector<int32_t> ret(last, last + (row_index+1));

			free(last);
			free(curr);

			return ret;
		}
};

int main()
{
	Solution solution;

	int row_index = 3;
	std::vector<int> res = solution.getRow(row_index);

	for (auto &i : res) {
		std::cout << i << ' ';
	}

	std::cout << std::endl;

	return 0;
}
