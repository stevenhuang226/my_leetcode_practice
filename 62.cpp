#include "shdstd-cpp.h"

class Solution
{
	private:
		int64_t combinatorial(int64_t n, int64_t k)
		{
			int64_t i;
			int64_t numerator = n - k + 1;
			int64_t res = 1;

			k = MIN(k, n - k);

			for (i = 1; i <= k; i++) {
				res = (res * numerator) / i;
				++numerator;
			}

			return res;
		}
	public:
		int64_t uniquePaths(int a, int b)
		{
			int64_t k = std::min(a - 1, b - 1);
			int64_t res = combinatorial(a+b-2, k);
			return (int)res;
		}
};

int main()
{
	Solution solution;

	int a;
	int b;

	std::cin >> a;
	std::cin >> b;

	int64_t res = solution.uniquePaths(a, b);

	std::cout << "res:" << res << std::endl;

	return 0;
}
