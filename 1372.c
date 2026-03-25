#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

enum {
	LEFT,	// tell node if you go left, combo keep
	RIGHT	// tell node if you go right, combo keep
};

int g_counter;

void dig(struct TreeNode *node, int combo, int8_t direction)
{
	if (node == NULL) {
		return;
	}

	g_counter = MAX(g_counter, combo);

	if (direction == LEFT) {
		dig(node->left, combo + 1, RIGHT);	// we have built combo link, if there is left node. It will get combo + 1 link
		dig(node->right, 1, LEFT);		// the way go to right node, build a new link, init as 1
		return;
	}

	if (direction == RIGHT) {
		dig(node->right, combo + 1, LEFT);
		dig(node->left, 1, RIGHT);
		return;
	}
}


int longestZigZag(struct TreeNode *root)
{
	g_counter = 0;

	dig(root, 0, LEFT);	// because it a root. There is no node before this. Set combo as 0
	dig(root, 0, RIGHT);

	return g_counter;
}
