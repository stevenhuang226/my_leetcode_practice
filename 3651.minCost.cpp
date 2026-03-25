#include "shdstd-cpp.h"
using namespace std;

#define INF32 (INT32_MAX / 4)

int d_row[] = {1,0};
int d_col[] = {0,1};
int d_size = 2;

typedef struct {
	int row;
	int col;
	int value;
} Cell;

struct State {
	int cost;
	int row;
	int col;
	int used;

	bool operator > (const State &other) const {
		return cost > other.cost;
	}
};

class Solution {
	public:
		int minCost(vector<vector<int>> &grid, int tele_lim) {
			int rows = grid.size();
			int cols = grid[0].size();

			vector<Cell> cells(rows * cols);
			vector<int> layer_ptr(tele_lim+1, 0);
			int cells_size = rows * cols;

			vector<vector<vector<int>>> cost(
					tele_lim+1,
					vector<vector<int>>(
						rows,
						vector<int>(cols, INF32)
						)
					);

			for (int r = 0; r < rows; ++r) {
				for (int c = 0; c < cols; ++c) {
					cells[r*cols + c].row = r;
					cells[r*cols + c].col = c;
					cells[r*cols + c].value = grid[r][c];
				}
			}

			sort(cells.begin(), cells.end(), [](const Cell &l, const Cell &r) {
					return l.value < r.value;
					});

			priority_queue<State, vector<State>, greater<State>> cost_queue;

			cost_queue.push((State){0, 0, 0, 0});
			cost[0][0][0] = 0;

			while (! cost_queue.empty()) {
				State from = cost_queue.top();
				cost_queue.pop();

				int fr = from.row;
				int fc = from.col;
				int fu = from.used;

				if (from.cost != cost[fu][fr][fc]) {
					continue;
				}

				for (int d = 0; d < d_size; ++d) {
					int nr = fr + d_row[d];
					int nc = fc + d_col[d];

					if (nr >= rows || nc >= cols) {
						continue;
					}

					int new_cost = cost[fu][fr][fc] + grid[nr][nc];

					if (cost[fu][nr][nc] <= new_cost) {
						continue;
					}
					cost[fu][nr][nc] = new_cost;
					cost_queue.push((State){new_cost, nr, nc, fu});
				}

				if (fu >= tele_lim) {
					continue;
				}

				int from_value = grid[fr][fc];
				int &cells_ptr = layer_ptr[fu];
				while (cells_ptr < cells_size &&
						cells[cells_ptr].value <= from_value) {
					int nr = cells[cells_ptr].row;
					int nc = cells[cells_ptr].col;
					int nu = fu + 1;
					++cells_ptr;

					int new_cost = cost[fu][fr][fc];

					if (cost[nu][nr][nc] <= new_cost) {
						continue;
					}
					cost[nu][nr][nc] = new_cost;
					cost_queue.push((State){new_cost, nr, nc, nu});
				}
			}

			int min_cost = INF32;
			for (int used = 0; used < tele_lim + 1; ++used) {
				min_cost = min(min_cost, cost[used][rows-1][cols-1]);
			}

			if (min_cost == INF32) {
				return -1;
			}
			return min_cost;
		}
};
