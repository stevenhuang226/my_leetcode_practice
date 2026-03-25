#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};


void swap_node(struct TreeNode *a, struct TreeNode *b)
{
	struct TreeNode *al = a->left;
	struct TreeNode *ar = a->right;

	a->left = b->left;
	a->right = b->right;

	b->left = al;
	b->right = ar;
}

struct TreeNode *deleteNode(struct TreeNode *root, int key)
{
}
