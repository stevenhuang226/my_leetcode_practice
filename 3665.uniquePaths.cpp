#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int dz = 2;
	int dr[2] = {0,1};
	int dc[2] = {1,0};

	int64_t mod = 1e9 + 7;

	struct node {
		int r;
		int c;
	};
public:
	int uniquePaths(vector<vector<int>> &grid) {
		int uniqueCount = 0;

		size_t rows = grid.size();
		size_t cols = grid[0].size();

		vector<vector<vector<node>>> target(2,
			vector<vector<node>>(rows,
				vector<node>(cols, (node){-1, -1})
			)
		);
		for (int r = rows-1; r >= 0; --r) {
			for (int c = cols-1; c >= 0; --c) {
				for (int d = 0; d < dz; ++d) {
					int sr = r - dr[d];
					int sc = c - dc[d];

					if (sr < 0 || sc < 0)
						continue;

					if (grid[r][c] != 1) {
						target[d][sr][sc] = (node){r, c};
						continue;
					}

					int nd = (d+1) % dz;
					target[d][sr][sc] = target[nd][r][c];
				}
			}
		}

		vector<vector<int>> ways(rows, vector<int>(cols, 0));
		ways[0][0] = 1;

		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				for (int d = 0; d < dz; ++d) {
					int tr = target[d][r][c].r;
					int tc = target[d][r][c].c;

					if (tr < 0 || tc < 0)
						continue;

					ways[tr][tc] = ((int64_t)ways[tr][tc] + ways[r][c]) % mod;
				}
			}
		}

		return ways[rows-1][cols-1];
	}
};
