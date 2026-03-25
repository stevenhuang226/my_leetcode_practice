#include "shdstd.h"

/*
 * auth: stevenhuang.dog@gmail.com
 * with chatgpt help
 */
#define DEF_TREE_VAL 0
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
	int max_value;
	int min_value;
	int lazy_add;
} SegmentNode;

SegmentNode *tree;

void build_tree(int node, int left, int right)
{
	tree[node].lazy_add = 0;
	tree[node].max_value = DEF_TREE_VAL;
	tree[node].min_value = DEF_TREE_VAL;

	if (left == right) {
		return;
	}

	int mid = (left + right) / 2;
	build_tree(node * 2, left, mid);
	build_tree(node * 2 + 1, mid + 1, right);
}

void push_down(int node)
{
	int lazy = tree[node].lazy_add;
	if (lazy == 0) {
		return;
	}

	int left_child = node * 2;
	int right_child = node * 2 + 1;

	tree[left_child].max_value += lazy;
	tree[left_child].min_value += lazy;
	tree[right_child].max_value += lazy;
	tree[right_child].min_value += lazy;

	tree[left_child].lazy_add += lazy;
	tree[right_child].lazy_add += lazy;

	tree[node].lazy_add = 0;
}

void range_add(int node, int left, int right,
		int add_left, int add_right, int value)
{
	if (add_left <= left && right <= add_right) {
		tree[node].max_value += value;
		tree[node].min_value += value;
		tree[node].lazy_add += value;
		return;
	}

	push_down(node);

	int mid = (left + right) / 2;

	if (add_left <= mid) {
		range_add(node * 2, left, mid, add_left, add_right, value);
	}
	if (mid + 1 <= add_right) {
		range_add(node * 2 + 1, mid + 1, right, add_left, add_right, value);
	}

	int left_max = tree[node * 2].max_value;
	int left_min = tree[node * 2].min_value;
	int right_max = tree[node * 2 + 1].max_value;
	int right_min = tree[node * 2 + 1].min_value;
	tree[node].max_value = MAX(left_max, right_max);
	tree[node].min_value = MIN(left_min, right_min);
}

int find_balance(int node, int left, int right, int limit_right)
{
	if (left > limit_right) {
		return -1;
	}

	if (left == right && tree[node].min_value == 0) {
		return left;
	}

	if (tree[node].max_value < 0 || tree[node].min_value > 0) {
		return -1;
	}

	push_down(node);

	int mid = (left + right) / 2;

	int result = find_balance(node * 2, left, mid, limit_right);
	if (result < 0 && mid+1 <= limit_right) {
		result = find_balance(node * 2 + 1, mid + 1, right, limit_right);
	}

	return result;
}

int longestBalanced(int *nums, int size)
{
	int exp_max = 1e5 + 8;

	int end = size-1;

	tree = malloc(size * 4 * sizeof(SegmentNode));
	build_tree(1, 0, end);

	int *prev = malloc(exp_max * sizeof(int));
	memset(prev, 0xFF, exp_max * sizeof(int));

	int best_length = 0;

	for (int r = 0; r < size; ++r) {
		int num = nums[r];

		int delta = (num % 2 == 0) - num % 2;
		range_add(1, 0, end, prev[num] + 1, r, delta);
		prev[num] = r;

		int limit_right = r - best_length;
		int left_most_balance = find_balance(1, 0, end, limit_right);
		if (left_most_balance >= 0) {
			best_length = MAX(best_length, r - left_most_balance + 1);
		}
	}

	free(tree);
	free(prev);

	return best_length;
}
