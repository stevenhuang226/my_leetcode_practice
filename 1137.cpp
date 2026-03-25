#include "shdstd-cpp.h"

class Solution
{
public:
	int tribonacci(int n)
	{
		int size = std::max(n+1, 4);
		int arr[size];

		arr[0] = 0;
		arr[1] = 1;
		arr[2] = 1;

		for (int i = 3; i <= n; ++i) {
			arr[i] = arr[i-1] + arr[i-2] + arr[i-3];
		}

		return arr[n];
	}
};
