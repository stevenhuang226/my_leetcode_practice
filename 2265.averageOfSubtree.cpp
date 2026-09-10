#include "shdstd-cpp.h"

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
	struct State {
		int val;
		int cnt;
	};

	int resCnt = 0;
private:
	State dfs(TreeNode *curr) {
		if (curr == NULL)
			return (State){0, 0};

		int val = curr->val;
		int cnt = 1;
		State l = dfs(curr->left);
		State r = dfs(curr->right);

		val += l.val;
		val += r.val;

		cnt += l.cnt;
		cnt += r.cnt;

		int avg = val / cnt;
		if (avg == curr->val) {
			++resCnt;
		}

		return (State){val, cnt};
	}
public:
	int averageOfSubtree(TreeNode *root) {
		State r = dfs(root);
		return resCnt;
	}
};
