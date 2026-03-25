#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MOD 1000000007

int sum(struct TreeNode *node)
{
	if (node == NULL) {
		return 0;
	}

	int left_val = sum(node->left);
	int right_val = sum(node->right);
	int curr_val = node->val;

	node->val = left_val + right_val + curr_val;

	return node->val;
}

int maxProduct(struct TreeNode *root)
{
	sum(root);

	int64_t root_sum = root->val;

	int64_t max = INT64_MIN;

	int quene_capacity = 1000;
	struct TreeNode **quene = malloc(quene_capacity * sizeof(struct TreeNode));
	int quene_size = 0;
	struct TreeNode **next = malloc(quene_capacity * sizeof(struct TreeNode));
	int next_size = 0;

	if (root->left != NULL) {
		quene[quene_size++] = root->left;
	}
	if (root->right != NULL) {
		quene[quene_size++] = root->right;
	}

	while (quene_size) {
		for (int i = 0; i < quene_size; ++i) {
			int64_t cutted_sum = quene[i]->val;
			int64_t production = cutted_sum * (root_sum - cutted_sum);
			max = MAX(max, production);

			if (quene[i]->left != NULL) {
				next[next_size++] = quene[i]->left;
			}
			if (quene[i]->right != NULL) {
				next[next_size++] = quene[i]->right;
			}
		}

		struct TreeNode **tmp;
		tmp = quene;
		quene = next;
		next = tmp;

		quene_size = next_size;
		next_size = 0;
	}
	
	free(quene);
	free(next);

	return max % MOD;
}
