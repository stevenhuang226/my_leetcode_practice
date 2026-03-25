#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct TreeNode *replace(struct TreeNode *node)
{
	if (node->left == NULL && node->right == NULL) {
		return NULL;
	}

	struct TreeNode *old_left = node->left;
	struct TreeNode *old_right = node->right;

	if (node->left != NULL) {
		if (node->left->right == NULL) {
			node->left->right = old_right;
			return node->left;
		}

		struct TreeNode *last = node->left;
		struct TreeNode *curr = node->left->right;

		while (curr->right != NULL) {
			last = curr;
			curr = curr->right;
		}

		last->right = curr->left;
		curr->left = old_left;
		curr->right = old_right;

		return curr;
	}
	
	if (node->right->left == NULL) {
		node->right->left = old_left;
		return node->right;
	}

	struct TreeNode *last = node->right;
	struct TreeNode *curr = node->right->left;

	while (curr->left != NULL) {
		last = curr;
		curr = curr->left;
	}

	last->left = curr->right;
	curr->left = old_left;
	curr->right = old_right;

	return curr;
}

struct TreeNode *deleteNode(struct TreeNode *root, int key)
{
	if (root == NULL) {
		return NULL;
	}

	if (root->val == key) {
		return replace(root);
	}

	struct TreeNode *node = root;

	while (node != NULL) {
		if (node->left != NULL && node->left->val == key) {
			node->left = replace(node->left);
			return root;
		}
		if (node->right != NULL && node->right->val == key) {
			node->right = replace(node->right);
			return root;
		}

		if (key < node->val) {
			node = node->left;
		} else {
			node = node->right;
		}
	}

	return root;
}
