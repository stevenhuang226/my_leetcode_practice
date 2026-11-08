#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	struct UnionFind {
		size_t size;
		vector<int> data;
		vector<int> sum;

		explicit UnionFind(size_t sz) {
			size = sz;
			data = vector<int>(sz);
			sum = vector<int>(sz, 1);
			for (int i = 0; i < sz; ++i) {
				data[i] = i;
			}
		}

		int find(int target) {
			if (data[target] != target)
				data[target] = find(data[target]);
			return data[target];
		}

		void link(int a, int b) {
			int rootA = find(a);
			int rootB = find(b);

			if (rootA == rootB)
				return;

			data[rootA] = rootB;
			sum[rootB] += sum[rootA];
		}

		bool isUnion(int a, int b) {
			return find(a) == find(b);
		}
	};
public:
	int countServers(vector<vector<int>> &grid) {
		int rows = grid.size();
		int cols = grid[0].size();

		UnionFind uf = UnionFind(rows * cols);

		for (int r = 0; r < rows; ++r) {
			int prevId = -1;
			for (int c = 0; c < cols; ++c) {
				if (grid[r][c] != 1)
					continue;
				int id = r * cols + c;
				if (prevId >= 0)
					uf.link(prevId, id);
				prevId = id;
			}
		}

		for (int c = 0; c < cols; ++c) {
			int prevId = -1;
			for (int r = 0; r < rows; ++r) {
				if (grid[r][c] != 1)
					continue;
				int id = r * cols + c;
				if (prevId >= 0)
					uf.link(prevId, id);
				prevId = id;
			}
		}

		int sum = 0;
		vector<bool> visitedRoot(rows * cols, false);
		for (int i = 0; i < rows * cols; ++i) {
			int root = uf.find(i);

			if (visitedRoot[root])
				continue;

			visitedRoot[root] = true;
			int s = uf.sum[root];
			sum += (s > 1) ? s : 0;
		}

		return sum;
	}
};
