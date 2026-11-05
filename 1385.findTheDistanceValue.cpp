#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int findTheDistanceValue(vector<int> &arr1, vector<int> &arr2, int d) {
		int cnt = 0;
		for (int i = 0; i < arr1.size(); ++i) {
			bool brk = false;
			for (int i2 = 0; i2 < arr2.size(); ++i2) {
				int dis = abs(arr1[i] - arr2[i2]);
				if (dis <= d) {
					brk = true;
					break;
				}
			}
			if (!brk)
				++cnt;
		}

		return cnt;
	}
};
