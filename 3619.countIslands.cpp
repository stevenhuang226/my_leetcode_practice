#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct UnionFind {
		size_t size;
		vector<int> parent;
		vector<int64_t> sum;

		explicit UnionFind(size_t sz)
		: parent(sz), size(sz), sum(sz) {
			for (int i = 0; i < sz; ++i) {
				parent[i] = i;
				sum[i] = 0;
			}
		}

		int find(int target) {
			if (parent[target] != target) {
				parent[target] = find(parent[target]);
			}
			return parent[target];
		}

		void setSum(int root, int score) {
			sum[root] = score;
		}

		void unite(int a, int b) {
			int rootA = find(a);
			int rootB = find(b);

			if (rootA == rootB)
				return;

			parent[rootA] = rootB;
			sum[rootB] += sum[rootA];
		}

		bool connected(int a, int b) {
			return find(a) == find(b);
		}
	};

	int dz = 2;
	int dr[2] = {0,-1};
	int dc[2] = {-1,0};
public:
	int countIslands(vector<vector<int>> &grid, int k) {
		size_t rows = grid.size();
		size_t cols = grid[0].size();

		UnionFind uf(rows * cols);

		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				int score = grid[r][c];
				if (score == 0)
					continue;

				int id = r * cols + c;
				uf.setSum(id, score);

				for (int d = 0; d < dz; ++d) {
					int nr = r + dr[d];
					int nc = c + dc[d];

					if (nr < 0 || nr >= rows
					|| nc < 0 || nc >= cols)
						continue;

					if (grid[nr][nc] == 0)
						continue;

					uf.unite(id, nr * cols + nc);
				}
			}
		}

		int res = 0;
		for (int i = 0; i < rows * cols; ++i) {
			int root = uf.find(i);
			if (uf.sum[root] <= 0 || uf.sum[root] % k != 0)
				continue;
			++res;
			uf.sum[root] = 0;
		}

		return res;
	}
};
