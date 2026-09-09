#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	vector<vector<vector<double>>> mem;

	int dr[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
	int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};
	int dz = 8;

	int sz;

	double dfs(int step, int r, int c) {
		if (step <= 0 && r >= 0 && r < sz && c >= 0 && c < sz)
			return 1.0;

		if (mem[step][r][c] != -1.0) {
			return mem[step][r][c];
		}

		double res = 0;
		for (int i = 0; i < dz; ++i) {
			int nr = r + dr[i];
			int nc = c + dc[i];

			if (nr < 0 || nr >= sz || nc < 0 || nc >= sz) {
				continue;
			}

			res += dfs(step-1, nr, nc) / dz;
		}

		mem[step][r][c] = res;
		return res;
	}

public:
	double knightProbability(int size, int k, int sR, int sC) {
		sz = size;

		mem = vector<vector<vector<double>>>(
				k + 1,
				vector<vector<double>>(
					size,
					vector<double>(size, -1.0)
				)
			);

		return dfs(k, sR, sC);
	}
};
