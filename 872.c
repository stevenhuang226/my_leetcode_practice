#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define MAX_LEAF_SIZE 204

int *leaf;
int leaf_size;
int leaf_comp;

void dig(struct TreeNode *node)
{
	if (node->left == NULL && node->right == NULL) {
		leaf[leaf_size++] = node->val;
		return;
	}

	if (node->left) {
		dig(node->left);
	}
	if (node->right) {
		dig(node->right);
	}

	return;
}

bool comp(struct TreeNode *node)
{
	if (node->left == NULL && node->right == NULL) {
		if (leaf[leaf_comp++] == node->val) {
			return true;
		} else {
			return false;
		}
	}

	bool res = true;
	if (node->left) {
		res &= comp(node->left);
	}
	if (node->right) {
		res &= comp(node->right);
	}

	return res;
}

bool leafSimilar(struct TreeNode *root1, struct TreeNode *root2)
{
	leaf = malloc(MAX_LEAF_SIZE * sizeof(int));
	leaf_size = 0;
	leaf_comp = 0;
	dig(root1);
	bool res = comp(root2);
	res &= (leaf_size == leaf_comp);
	free(leaf);
	return res;
}
