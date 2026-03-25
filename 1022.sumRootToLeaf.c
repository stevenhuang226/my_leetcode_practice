#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

uint32_t sum;

void dfs(struct TreeNode *node, uint32_t code)
{
	if (node == NULL) {
		return;
	}

	code = (code << 1) | node->val;

	if (node->left == NULL && node->right == NULL) {
		sum += code;
		return;
	}

	dfs(node->left, code);
	dfs(node->right, code);
}

int sumRootToLeaf(struct TreeNode *root)
{
	sum = 0;
	dfs(root, 0);
	return sum;
}
