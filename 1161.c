#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MAX_TREE_SIZE 10004

int maxLevelSum(struct TreeNode *root)
{
	struct TreeNode **quene = malloc(MAX_TREE_SIZE * sizeof(struct TreeNode *));
	int quene_size = 0;

	struct TreeNode **next = malloc(MAX_TREE_SIZE * sizeof(struct TreeNode *));
	int next_size = 0;

	quene[quene_size++] = root;

	int max = INT_MIN;
	int max_level = -1;
	int curr_level = 1;

	while (quene_size > 0) {

		int sum = 0;
		for (int i = 0; i < quene_size; ++i) {
			struct TreeNode *node = quene[i];

			sum += node->val;

			if (node->left != NULL) {
				next[next_size++] = node->left;
			}
			if (node->right != NULL) {
				next[next_size++] = node->right;
			}
		}

		if (sum > max) {
			max = sum;
			max_level = curr_level;
		}
		++curr_level;

		struct TreeNode **tmp;

		tmp = quene;
		quene = next;
		next = tmp;

		quene_size = next_size;
		next_size = 0;
	}

	free(quene);
	free(next);
	return max_level;
}
