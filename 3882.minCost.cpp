#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int maxNumberCount = 1024;

	int dz = 2;
	int dr[2] = {0,1};
	int dc[2] = {1,0};
public:
	int minCost(vector<vector<int>> &grid) {
		size_t rows = grid.size();
		size_t cols = grid[0].size();

		vector<vector<vector<bool>>> dp(
		rows, vector<vector<bool>>(
			cols, vector<bool>(
				maxNumberCount, false
			)
		));

		dp[0][0][grid[0][0]] = true;

		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				for (int d = 0; d < dz; ++d) {
					int nr = r + dr[d];
					int nc = c + dc[d];

					if (nr >= rows || nc >= cols)
						continue;

					int num = grid[nr][nc];

					for (int i = 0; i < maxNumberCount; ++i) {
						if (!dp[r][c][i])
							continue;

						int x = i ^ num;

						dp[nr][nc][x] = true;
					}
				}
			}
		}

		for (int i = 0; i < maxNumberCount; ++i) {
			if (dp[rows-1][cols-1][i])
				return i;
		}
		return -1;
	}
};
