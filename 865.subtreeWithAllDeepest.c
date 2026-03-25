#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int g_deepest;
struct TreeNode *g_deepest_node;

int dfs(struct TreeNode *node, int depth)
{
	if (node == NULL) {
		return depth;
	}

	int left_depth = dfs(node->left, depth + 1);
	int right_depth = dfs(node->right, depth + 1);

	if (left_depth == right_depth && g_deepest <= left_depth) {
		g_deepest = left_depth;
		g_deepest_node = node;
	}

	return MAX(left_depth, right_depth);
}

struct TreeNode *subtreeWithAllDeepest(struct TreeNode *root)
{
	g_deepest = 0;
	g_deepest_node = root;

	dfs(root, 0);

	return g_deepest_node;
}
