#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define EXP_SIZE (1e4 + 8)

struct TreeNode **inorder;
int count;

int cmpTreeNode(const void *l, const void *r)
{
	int lv = (*(struct TreeNode **)l)->val;
	int rv = (*(struct TreeNode **)r)->val;

	if (lv > rv) {
		return 1;
	} else if (rv < lv) {
		return -1;
	} else {
		return 0;
	}
}

void dfs(struct TreeNode *node)
{
	if (node == NULL) {
		return;
	}

	dfs(node->left);
	dfs(node->right);

	inorder[count++] = node;
}

struct TreeNode *build(int left, int right)
{
	if (left > right) {
		return NULL;
	}

	int mid = (left + right) / 2;

	inorder[mid]->left = build(left, mid - 1);
	inorder[mid]->right = build(mid + 1, right);

	return inorder[mid];
}

struct TreeNode *balanceBST(struct TreeNode *root)
{
	if (root == NULL) {
		return 0;
	}
	inorder = malloc(EXP_SIZE * sizeof(struct TreeNode *));
	count = 0;

	dfs(root);
	qsort(inorder, count, sizeof(struct TreeNode *), cmpTreeNode);

	struct TreeNode *res = build(0, count - 1);

	free(inorder);

	return res;
}
