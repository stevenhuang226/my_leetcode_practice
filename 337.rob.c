#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static inline int smax(const int a, const int b)
{
	return MAX(a, b);
}

typedef struct {
	int rob;
	int skip;
} Node;

Node dfs(struct TreeNode *curr)
{
	Node curr_node;
	if (curr == NULL) {
		curr_node.skip = 0;
		curr_node.rob = 0;
		return curr_node;
	}

	Node left_node = dfs(curr->left);
	Node right_node = dfs(curr->right);

	curr_node.skip = smax(left_node.skip, left_node.rob) + smax(right_node.skip, right_node.rob);
	curr_node.rob = curr->val + left_node.skip + right_node.skip;

	return curr_node;
}

int rob(struct TreeNode *root)
{
	Node root_node = dfs(root);
	return smax(root_node.skip, root_node.rob);
}
