#include "shdstd-cpp.h"

using namespace std;

class Solution {
public:
	int largestOverlap(vector<vector<int>> &imga, vector<vector<int>> &imgb) {
		int rows = imga.size();
		int cols = imga[0].size();

		int bestOverlay = 0;
		for (int offR = -(rows - 1); offR < rows; ++offR) {
			for (int offC = -(cols - 1); offC < cols; ++offC) {
				int currOverlay = 0;
				for (int r = 0; r < rows; ++r) {
					for (int c = 0; c < cols; ++c) {
						int br = r + offR;
						int bc = c + offC;
						if (br < 0 || br >= rows)
							continue;
						if (bc < 0 || bc >= cols)
							continue;
						if (imga[r][c] + imgb[br][bc] == 2) {
							bestOverlay = max(bestOverlay, ++currOverlay);
						}
					}
				}
			}
		}

		return bestOverlay;
	}
};
