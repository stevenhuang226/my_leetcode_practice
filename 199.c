#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

#define VIEW_SIZE 100
#define VIEW_DEFAUL (-200)

int *rightSideView(struct TreeNode *root, int *p_ret_size)
{
	if (root == NULL) {
		*p_ret_size = 0;
		return NULL;
	}

	/* put answer in here */
	int *view = malloc(VIEW_SIZE * sizeof(int));
	int view_size = 0;
	for (int i = 0; i < VIEW_SIZE; ++i) {
		view[i] = VIEW_DEFAUL;
	}

	/* main quene, process on this */
	struct TreeNode **quene = malloc(VIEW_SIZE * sizeof(struct TreeNode *));
	int quene_size = 0;

	/* next quene, the quene next round will use */
	struct TreeNode **next = malloc(VIEW_SIZE * sizeof(struct TreeNode *));
	int next_size = 0;

	quene[quene_size++] = root;

	while (quene_size > 0) {

		view[view_size] = quene[0]->val;

		for (int i = 0; i < quene_size; ++i) {
			struct TreeNode *node = quene[i];

			if (node->right != NULL) {	/* push right first, it will make sure quene[0] in next round is most right */
				next[next_size++] = node->right;
			}
			if (node->left != NULL) {
				next[next_size++] = node->left;
			}
		}

		++view_size;

		/* swap quene, next */
		struct TreeNode **tmp;
		tmp = quene;
		quene = next;
		next = tmp;

		quene_size = next_size;
		next_size = 0;
	}

	free(quene);
	free(next);

	*p_ret_size = view_size;
	return view;
}
