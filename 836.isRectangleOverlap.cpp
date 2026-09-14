#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	bool isRectangleOverlap(vector<int> &reca, vector<int> &recb) {
		if (reca[2] <= recb[0] || recb[2] <= reca[0])
			return false;
		if (reca[3] <= recb[1] || recb[3] <= reca[1])
			return false;

		return true;
	}
};
