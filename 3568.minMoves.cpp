#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct State {
		int r;
		int c;
		uint32_t mask;
		int energy;
	};

	int ds = 4;
	int dr[4] = {0, 1, 0, -1};
	int dc[4] = {1, 0, -1, 0};

public:
	int minMoves(vector<string> &classroom, int energy) {
		int rows = classroom.size();
		int cols = classroom[0].length();

		int l_count = 0;
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				if (classroom[r][c] != 'L')
					continue;

				classroom[r][c] = ++l_count;
			}
		}

		queue<State> q;
		vector<vector<vector<int>>> visited(
			rows,
			vector<vector<int>>(
				cols,
				vector<int>(1 << l_count, -1)
			)
		);

		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				if (classroom[r][c] != 'S')
					continue;

				q.push({r, c, 0, energy});
				break;
			}
		}

		uint32_t fullMask = (1 << l_count) - 1;
		int step = 0;
		while (!q.empty()) {
			size_t sz = q.size();
			while (sz--) {
				State curr = q.front();
				q.pop();

				if (curr.mask == fullMask) {
					return step;
				}

				for (int i = 0; i < ds; ++i) {
					int nr = curr.r + dr[i];
					int nc = curr.c + dc[i];

					if (nr < 0 || nr >= rows || nc < 0 || nc >= cols)
						continue;

					if (classroom[nr][nc] == 'X')
						continue;

					uint32_t newMask = curr.mask;
					int newEnergy = curr.energy - 1;

					if (classroom[nr][nc] >= 1 && classroom[nr][nc] <= 10) {
						newMask |= 1 << (classroom[nr][nc]-1);
					}

					if (newEnergy < 0)
						continue;
					if (classroom[nr][nc] == 'R') {
						newEnergy = energy;
					}

					if (visited[nr][nc][newMask] >= newEnergy)
						continue;

					visited[nr][nc][newMask] = newEnergy;
					q.push({nr, nc, newMask, newEnergy});
				}
			}
			++step;
		}

		return -1;
	}
};
