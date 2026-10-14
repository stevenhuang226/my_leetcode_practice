#include "shdstd-cpp.h"
using namespace std;

class Solution {
public:
	string maxSumOfSquares(int num, int sum) {
		if (num * 9 < sum) {
			return "";
		}

		string res = "";
		int i;
		for (i = 0; i < num; ++i) {
			if (sum <= 9) {
				res += sum + '0';
				++i;
				break;
			}
			res += "9";
			sum -= 9;
		}
		for (; i < num; ++i) {
			res += "0";
		}

		return res;
	}
};
