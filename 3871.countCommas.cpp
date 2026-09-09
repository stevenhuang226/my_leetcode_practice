#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int64_t countCommas(int64_t n) {
		int64_t cnt = 0;

		cnt += max((int64_t)0, n - 999);
		cnt += max((int64_t)0, n - 999999);
		cnt += max((int64_t)0, n - 999999999);
		cnt += max((int64_t)0, n - 999999999999);
		cnt += max((int64_t)0, n - 999999999999999);

		return cnt;
	}
};
