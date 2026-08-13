#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int dr[4] = {0, 1, 0, -1};
	int dc[4] = {1, 0, -1, 0};
	int dz = 4;

public:
	vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
		int rows = mat.size();
		int cols = mat[0].size();

		queue<pair<int, int>> q;
		vector<vector<int>> res(rows, vector<int>(cols, -1));

		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				if (mat[r][c] == 0) {
					q.push({r, c});
					res[r][c] = 0;
				}
			}
		}


		while (!q.empty()) {
			auto [r, c] = q.front();
			q.pop();

			for (int i = 0; i < dz; ++i) {
				int nr = r + dr[i];
				int nc = c + dc[i];

				if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
					continue;
				if (res[nr][nc] >= 0)
					continue;

				res[nr][nc] = res[r][c] + 1;
				q.push({nr, nc});
			}
		}

		return res;
	}
};
