#include "shdstd.h"

#define CHARID(x) ((x) - 'a')

typedef struct TrieNode TrieNode;

struct TrieNode {
	uint16_t best;
	uint16_t min_len;
	TrieNode *child[26];
};

void trienode_cleaner(TrieNode *curr)
{
	for (int i = 0; i < 26; ++i) {
		if (curr->child[i] != NULL) {
			trienode_cleaner(curr->child[i]);
		}
	}

	free(curr);
}

int *stringIndices(
		char **container, int container_size,
		char **query, int query_size,
		int *ret_size)
{
	TrieNode *head = calloc(1, sizeof(TrieNode));
	head->best = -1;
	head->min_len = UINT16_MAX;

	for (int i = 0; i < container_size; ++i) {
		int len = strlen(container[i]);
		int ptr = len;

		TrieNode *curr = head;

		if (len < head->min_len) {
			head->min_len = len;
			head->best = i;
		}

		while (ptr--) {
			int id = CHARID(container[i][ptr]);

			if (curr->child[id] == NULL) {
				curr->child[id] = calloc(1, sizeof(TrieNode));
				curr->child[id]->min_len = UINT16_MAX;
			}

			curr = curr->child[id];

			if (len < curr->min_len) {
				curr->min_len = len;
				curr->best = i;
			}
		}
	}

	int *res = malloc(query_size * sizeof(int));
	*ret_size = query_size;

	for (int i = 0; i < query_size; ++i) {
		int len = strlen(query[i]);
		int ptr = len;
		TrieNode *curr = head;
		while (ptr--) {
			int id = CHARID(query[i][ptr]);

			if (curr->child[id] == NULL) {
				break;
			}

			curr = curr->child[id];
		}
		res[i] = curr->best;
	}

	trienode_cleaner(head);

	return res;
}
