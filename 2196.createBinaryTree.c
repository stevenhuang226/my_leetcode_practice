#include "shdstd.h"

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

typedef struct {
	int key;
	int left;
	int right;
} HashNode;

typedef struct {
	uint32_t size;
	uint32_t step;

	HashNode def;

	HashNode data[];
} HashMap;

HashMap *hm_create(int size)
{
	HashMap *map = malloc(sizeof(HashMap) + size * sizeof(HashNode));

	memset(map->data, 0xff, size * sizeof(HashNode));

	map->size = size;
	map->def.key = -1;
	map->def.left = -1;
	map->def.right = -1;

	map->step = 1;

	return map;
}

static inline uint32_t hash(int key, uint32_t size)
{
	return (uint32_t)key % size;
}

void hm_insert(HashMap *map, int key, int val, int is_left)
{
	uint32_t hashed = hash(key, map->size);

	while (map->data[hashed].key != map->def.key) {
		if (map->data[hashed].key == key) {
			if (is_left) {
				map->data[hashed].left = val;
			} else {
				map->data[hashed].right = val;
			}
		}

		hashed = hash(hashed + map->step, map->size);
	}

	map->data[hashed].key = key;
	if (is_left) {
		map->data[hashed].left = val;
	} else {
		map->data[hashed].right = val;
	}
}

HashNode *hm_search(HashMap *map, int key)
{
	uint32_t hashed = hash(key, map->size);
	while (map->data[hashed].key != map->def.key) {
		if (map->data[hashed].key == key) {
			return &map->data[hashed];
		}
		hashed = hash(hashed + map->step, map->size);
	}
	return NULL;
}

void dfs_build(struct TreeNode *node, HashMap *hm)
{
	int parent = node->val;
	HashNode *search = hm_search(hm, parent);

	node->left = node->right = NULL;

	if (search == NULL) {
		return;
	}

	if (search->left >= 0) {
		node->left = malloc(sizeof(struct TreeNode));
		node->left->val = search->left;
		dfs_build(node->left, hm);
	}

	if (search->right >= 0) {
		node->right = malloc(sizeof(struct TreeNode));
		node->right->val = search->right;
		dfs_build(node->right, hm);
	}
}

struct TreeNode *createBinaryTree(int **descriptions, int size, int *col_size)
{
	int exp_max = 1e5 + 8;

	HashMap *hm = hm_create(size * 3);

	int8_t *is_child = calloc(exp_max, sizeof(int8_t));

	for (int i = 0; i < size; ++i) {
		int parent = descriptions[i][0];
		int child = descriptions[i][1];
		int is_left = descriptions[i][2];

		is_child[child] = true;

		hm_insert(hm, parent, child, is_left);
	}

	int root = -1;
	for (int i = 0; i < hm->size; ++i) {
		int parent = hm->data[i].key;
		if (parent >= 0 && !is_child[parent]) {
			root = parent;
			break;
		}
	}

	struct TreeNode *head = malloc(sizeof(struct TreeNode));

	head->val = root;

	dfs_build(head, hm);

	free(hm);

	return head;
}
