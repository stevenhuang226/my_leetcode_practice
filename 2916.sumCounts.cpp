#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int64_t mod = 1e9 + 7;

	struct Node {
		int64_t lazy;
		int64_t sum;
	};

	void apply(vector<Node> &tree, int curr, int l, int r, int64_t val) {
		tree[curr].sum += val * (r - l + 1);
		tree[curr].lazy += val;
	}

	void push(vector<Node> &tree, int curr, int l, int r) {
		if (tree[curr].lazy == 0 || l == r)
			return;

		int mid = (l + r) / 2;
		apply(tree, curr * 2 + 1, l, mid, tree[curr].lazy);
		apply(tree, curr * 2 + 2, mid+1, r, tree[curr].lazy);

		tree[curr].lazy = 0;
	}

	void st_update(vector<Node> &tree, int curr,
		int l, int r, int ql, int qr, int64_t val) {
		if (qr < l || r < ql)
			return;
		if (ql <= l && r <= qr) {
			apply(tree, curr, l, r, val);
			return;
		}

		push(tree, curr, l, r);

		int mid = (l + r) / 2;
		st_update(tree, curr * 2 + 1, l, mid, ql, qr, val);
		st_update(tree, curr * 2 + 2, mid+1, r, ql, qr, val);

		tree[curr].sum =
			tree[curr * 2 + 1].sum + tree[curr * 2 + 2].sum;
	}

	int64_t st_query(vector<Node> &tree, int curr,
		int l, int r, int ql, int qr) {
		if (qr < l || ql > r)
			return 0;

		if (ql <= l && r <= qr)
			return tree[curr].sum;

		push(tree, curr, l, r);

		int mid = (l + r) / 2;
		return st_query(tree, curr * 2 + 1, l, mid, ql, qr) +
			st_query(tree, curr * 2 + 2, mid+1, r, ql, qr);
	}
public:
	int sumCounts(vector<int> &nums) {
		int res = 0;
		int64_t sum = 0;

		vector<int> last((size_t)1e5 + 8, -1);
		vector<Node> tree(nums.size() * 4, {0, 0});

		for (int i = 0; i < nums.size(); ++i) {
			int mid = last[nums[i]];

			int64_t rangeSum = st_query(tree, 0, 0, nums.size()-1, mid+1, i);
			st_update(tree, 0, 0, nums.size()-1, mid+1, i, 1);

			sum = sum + (2 * rangeSum) % mod;
			sum = (sum + (i - mid)) % mod;

			last[nums[i]] = i;

			res = (res + sum) % mod;
		}

		return res;
	}
};
