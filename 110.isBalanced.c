#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int dfs_depth(struct TreeNode *node, int depth)
{
	if (node == NULL) {
		return depth;
	}

	int left_depth = dfs_depth(node->left, depth);
	int right_depth = dfs_depth(node->right, depth);

	if (left_depth == -1 || right_depth == -1) {
		return -1;
	}

	if (abs(left_depth - right_depth) > 1) {
		return -1;
	}

	int d = MAX(left_depth, right_depth) + 1;
	return d;
}

bool isBalanced(struct TreeNode *root)
{
	if (root == NULL) {
		return true;
	}

	if (dfs_depth(root, 0) >= 0) {
		return true;
	}

	return false;
}
