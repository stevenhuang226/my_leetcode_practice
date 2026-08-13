#include "shdstd-cpp.h"

using namespace std;

class Solution {
	struct Node {
		int left;
		int right;
		int leftLength;
		int rightLength;
		int best;
	};

	vector<Node> tree;

	Node merge(const string &s, const Node &l, const Node &r) {
		Node result;

		result.left = l.left;
		result.right = r.right;

		result.leftLength = l.leftLength;
		result.rightLength = r.rightLength;

		result.best = max(l.best, r.best);

		int leftSize = l.right - l.left + 1;
		int rightSize = r.right - r.left + 1;

		if (s[l.right] == s[r.left]) {
			if (l.leftLength == leftSize)
				result.leftLength += r.leftLength;
			if (r.rightLength == rightSize)
				result.rightLength += l.rightLength;

			result.best = max(result.best, l.rightLength + r.leftLength);
		}

		return result;
	}

	void build(const string &s, int node, int left, int right) {
		if (left == right) {
			tree[node] = {
				left, right,
				1, 1, 1
			};
			return;
		}

		int mid = (left + right) / 2;

		build(s, node * 2 + 1, left, mid);
		build(s, node * 2 + 2, mid+1, right);

		tree[node] = merge(s, tree[node*2+1], tree[node*2+2]);
	}

	void update(const string &s, int node,
		int left, int right, int index) {
		if (left == right) {
			tree[node] = {
				left, right,
				1, 1, 1
			};
			return;
		}

		int mid = (left + right) / 2;

		if (index <= mid) {
			update(s, node * 2 + 1, left, mid, index);
		} else {
			update(s, node * 2 + 2, mid+1, right, index);
		}

		tree[node] = merge(s, tree[node*2+1], tree[node*2+2]);
	}

public:
	vector<int> longestRepeating(string s, string queryCharacters, vector<int> &queryIndices) {
		tree.resize(4 * s.size());

		build(s, 0, 0, s.size()-1);

		vector<int> result(queryIndices.size());

		for (int i = 0; i < queryIndices.size(); ++i) {
			int index = queryIndices[i];
			char ch = queryCharacters[i];

			s[index] = ch;

			update(s, 0, 0, s.size()-1, index);

			result[i] = tree[0].best;
		}

		return result;
	}
};
