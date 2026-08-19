#include "shdstd-cpp.h"

using namespace std;

class Solution{
public:
	int maxNumberOfFamilies(int rows, vector<vector<int>> &reservedSeats) {
		sort(reservedSeats.begin(), reservedSeats.end());

		int p = 0;
		int cnt = 0;

		int reservedRows = 0;

		while (p < reservedSeats.size()) {

			bool left, right, midL, midR;
			left = right = midL = midR = true;

			int r = reservedSeats[p][0];

			while (p < reservedSeats.size() && reservedSeats[p][0] == r) {
				int col = reservedSeats[p++][1];
				switch (col) {
					case 2:
					case 3:
						left = false;
						break;
					case 4:
					case 5:
						midL = false;
						break;
					case 6:
					case 7:
						midR = false;
						break;
					case 8:
					case 9:
						right = false;
						break;
					default:
						break;
				}
			}

			++reservedRows;

			if (left && midL) {
				++cnt;
			}
			if (midR && right) {
				++cnt;
			}

			if (!left && !right && midL && midR) {
				++cnt;
			}
		}

		return cnt + (rows - reservedRows) * 2;
	}
};
