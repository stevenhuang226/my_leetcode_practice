#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
int maxDepth(struct TreeNode *root)
{
	if (root == NULL) {
		return 0;
	}

	int left_depth = maxDepth(root->left);
	int right_depth = maxDepth(root->right);

	int max = MAX(left_depth, right_depth);

	return max + 1;
}
