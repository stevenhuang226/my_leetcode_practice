#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

int g_count;

void try(struct TreeNode *node, int target, int64_t *sum)
{
	if (node == NULL) {
		return;
	}

	(*sum) += node->val;
	if ((*sum) == target) {
		++g_count;
	}

	try(node->left, target, sum);
	try(node->right, target, sum);

	(*sum) -= node->val;
	return;
}

void dig(struct TreeNode *node, int target)
{
	if (node == NULL) {
		return;
	}

	int64_t sum = 0;
	try(node, target, &sum);

	dig(node->left, target);
	dig(node->right, target);

	return;
}

int pathSum(struct TreeNode *root, int target_sum)
{
	g_count = 0;

	dig(root, target_sum);

	return g_count;
}
