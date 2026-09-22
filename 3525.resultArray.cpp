#include "shdstd-cpp.h"

using namespace std;

#define MAX_K 5
class Solution {
private:
	struct Node {
		int product;
		int cnt[MAX_K];
	};

	vector<Node> tree;

	Node merge(const Node &left, const Node &right, int k) {
		Node res{};
		res.product = left.product * right.product % k;
		for (int r = 0; r < k; ++r) {
			res.cnt[r] += left.cnt[r];
		}
		for (int r = 0; r < k; ++r) {
			int nr = (int64_t)left.product * r % k;
			res.cnt[nr] += right.cnt[r];
		}
		return res;
	}

	void build(vector<int> &nums, int k, int curr, int l, int r) {
		if (l == r) {
			tree[curr] = {};
			tree[curr].cnt[nums[l] % k] = 1;
			tree[curr].product = nums[l] % k;
			return;
		}

		int mid = (l + r) / 2;
		build(nums, k, curr * 2 + 1, l, mid);
		build(nums, k, curr * 2 + 2, mid+1, r);
		tree[curr] = merge(tree[curr*2+1], tree[curr*2+2], k);
	}

	void update(int curr, int l, int r, int idx, int val, int k) {
		if (l == r) {
			tree[curr] = {};
			tree[curr].product = val % k;
			tree[curr].cnt[val % k] = 1;
			return;
		}

		int mid = (l + r) / 2;

		if (idx <= mid) {
			update(curr * 2 + 1, l, mid, idx, val, k);
		} else {
			update(curr * 2 + 2, mid+1, r, idx, val, k);
		}

		tree[curr] = merge(tree[curr*2+1], tree[curr*2+2], k);
	}

	Node query(int curr, int l, int r, int ql, int qr, int k) {
		if (ql <= l && r <= qr) {
			return tree[curr];
		}

		int mid = (l + r) / 2;
		if (qr <= mid) {
			return query(curr*2+1, l, mid, ql, qr, k);
		}
		if (ql > mid) {
			return query(curr*2+2, mid+1, r, ql, qr, k);
		}

		Node ln = query(curr*2+1, l, mid, ql, qr, k);
		Node rn = query(curr*2+2, mid+1, r, ql, qr, k);

		return merge(ln, rn, k);
	}
public:
	vector<int> resultArray(vector<int> &nums, int k, vector<vector<int>> &queries) {
		int sz = nums.size();
		tree.resize(sz * 4);

		build(nums, k, 0, 0, sz-1);

		vector<int> res;
		for (vector<int> q : queries) {
			int idx = q[0];
			int val = q[1];
			int l = q[2];
			int x = q[3];

			update(0, 0, sz-1, idx, val, k);

			Node qry = query(0, 0, sz-1, l, sz-1, k);

			res.push_back(qry.cnt[x]);
		}

		return res;
	}
};
