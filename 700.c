#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct TreeNode *searchBST(struct TreeNode *root, int target)
{
	struct TreeNode *node = root;

	while (node != NULL) {
		if (node->val == target) {
			return node;
		}

		if (target < node->val) {
			node = node->left;
			continue;
		} else {
			node = node->right;
			continue;
		}
	}

	return NULL;
}
