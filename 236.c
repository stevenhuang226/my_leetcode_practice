#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct TreeNode *g_answer;

int8_t find(struct TreeNode *node, int p, int q)
{
	if (node == NULL) {
		return 0;
	}

	int8_t got = 0;
	if (node->val == p || node->val == q) {
		++got;
	}

	got += find(node->left, p, q);
	got += find(node->right, p, q);

	if (got == 2 && g_answer == NULL) {
		g_answer = node;
		return 2;
	}

	return got;
}


struct TreeNode *lowestCommonAncestor(
		struct TreeNode *root,
		struct TreeNode *p,
		struct TreeNode *q)
{
	g_answer = NULL;

	find(root, p->val, q->val);

	return g_answer;
}
