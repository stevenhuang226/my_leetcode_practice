#include "shdstd-cpp.h"

using namespace std;

#define MAXPAR 108
class Solution {
public:
	bool hasValidPath(vector<vector<char>> &grid) {
		int rows = grid.size();
		int cols = grid[0].size();

		if (grid[0][0] == ')' || grid[rows-1][cols-1] == '(') {
			return false;
		}

		vector<vector<vector<bool>>> balance(rows,
			vector<vector<bool>>(cols,
				vector<bool>(MAXPAR, false)
			)
		);

		balance[0][0][1] = true;
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				if (grid[r][c] == '(') {
					for (int i = 1; i < MAXPAR; ++i) {
						if (r > 0) {
							balance[r][c][i] = balance[r-1][c][i-1];
						}
						if (c > 0) {
							balance[r][c][i] = balance[r][c][i] || balance[r][c-1][i-1];
						}
					}
				} else {
					for (int i = 0; i < MAXPAR-1; ++i) {
						if (r > 0) {
							balance[r][c][i] = balance[r-1][c][i+1];
						}
						if (c > 0) {
							balance[r][c][i] = balance[r][c][i] || balance[r][c-1][i+1];
						}
					}
				}
			}
		}

		return balance[rows-1][cols-1][0];
	}
};
