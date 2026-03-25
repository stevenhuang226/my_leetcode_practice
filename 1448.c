#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

void dig(struct TreeNode *node, int max, int *counter)
{
	if (node->val >= max) {
		++(*counter);
	}

	max = MAX(max, node->val);

	if (node->left != NULL) {
		dig(node->left, max, counter);
	}
	if (node->right != NULL) {
		dig(node->right, max, counter);
	}
	return;
}

int goodNodes(struct TreeNode *root)
{
	int count = 0;
	dig(root, root->val, &count);

	return count;
}
