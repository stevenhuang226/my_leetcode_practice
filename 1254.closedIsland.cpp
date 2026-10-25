#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct UnionFind {
		vector<int> parent;
		size_t sz;

		explicit UnionFind(size_t sz)
		: parent(sz), sz(sz) {
			for (int i = 0; i < sz; ++i) {
				parent[i] = i;
			}
		}

		int find(int target) {
			if (parent[target] != target) {
				parent[target] = find(parent[target]);
			}
			return parent[target];
		}

		void unite(int a, int b) {
			parent[find(a)] = find(b);
		}

		bool connected(int a, int b) {
			return find(a) == find(b);
		}
	};

	int dsz = 2;
	int dr[2] = {-1,0};
	int dc[2] = {0,-1};
public:
	int closedIsland(vector<vector<int>> &grid) {
		int rows = grid.size();
		int cols = grid[0].size();
		int sz = rows * cols;

		UnionFind uf(sz+1);

		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < cols; ++c) {
				int oid = r * cols + c;
				if (grid[r][c] != 0)
					continue;

				for (int d = 0; d < dsz; ++d) {
					int nr = r + dr[d];
					int nc = c + dc[d];

					if (nr < 0 || nr >= rows ||
					nc < 0 || nc >= cols)
						continue;
					if (grid[nr][nc] != 0)
						continue;

					int nid = nr * cols + nc;
					uf.unite(oid, nid);
				}
			}
		}

		for (int r = 0; r < rows; ++r) {
			int id = r * cols + 0;
			uf.unite(id, sz);
			id = r * cols + cols-1;
			uf.unite(id, sz);
		}

		for (int c = 0; c < cols; ++c) {
			int id = c;
			uf.unite(id, sz);
			id = (rows-1) * cols + c;
			uf.unite(id, sz);
		}

		vector<bool> visited(rows * cols, false);
		int closedCount = 0;
		for (int r = 1; r < rows-1; ++r) {
			for (int c = 1; c < cols-1; ++c) {
				if (grid[r][c] != 0)
					continue;

				int id = r * cols + c;
				int root = uf.find(id);
				if (root == sz || visited[root])
					continue;
				visited[root] = true;
				++closedCount;
			}
		}

		return closedCount;
	}
};
