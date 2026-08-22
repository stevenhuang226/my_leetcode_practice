#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	bool checkDivisibility(int n) {
		int sum = 0;
		int product = 1;

		int tmp = n;
		while (tmp) {
			sum += (tmp % 10);
			product *= (tmp % 10);

			tmp /= 10;
		}

		return !(n % (sum + product));
	}
};
