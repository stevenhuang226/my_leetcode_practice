#include "shdstd.h"

#define RET_TMP_SIZE 3001
#define CHAR_OFFSET (-('a'))

typedef struct Trie Trie;
struct Trie {
	Trie *next[26];
	int8_t is_end;
};

Trie *g_root;

void trie_insert(char *word)
{
	Trie *trie = g_root;

	char c;
	int ptr = 0;
	while ((c = word[ptr++]) != '\0') {
		int n = c + CHAR_OFFSET;

		if (trie->next[n]) {
			trie = trie->next[n];
			continue;
		}

		trie->next[n] = malloc(sizeof(Trie));
		trie->next[n]->is_end = false;

		for (int i = 0; i < 26; ++i) {
			trie->next[n]->next[i] = NULL;
		}

		trie = trie->next[n];
	}
	trie->is_end = true;
	return;
}

char *tmp;
int tmp_base;

char ***ret;
int ret_p1;
int ret_p2;

void tmpcpy(int offset)
{
	tmp[tmp_base + offset] = '\0';
	ret[ret_p1][ret_p2] = malloc((tmp_base + offset + 1) * sizeof(char));
	strcpy(ret[ret_p1][ret_p2], tmp);
	++ret_p2;
}

void suggest(Trie *node, int offset)
{
	if (node->is_end) {
		tmpcpy(offset);
		if (ret_p2 >= 3) {
			return;
		}
	}
	for (int i = 0; i < 26 && ret_p2 < 3; ++i) {
		if (node->next[i] == NULL) continue;
		tmp[tmp_base + offset] = i - CHAR_OFFSET;
		suggest(node->next[i], offset + 1);
	}
}

void trie_clean(Trie *node)
{
	for (int i = 0; i < 26; ++i) {
		if (node->next[i] == NULL) {
			continue;
		}
		trie_clean(node->next[i]);
	}
	free(node);
	return;
}

char ***suggestedProducts(
		char **products, int products_size,
		char *search_word,
		int *return_size, int **return_col_size)
{
	g_root = malloc(sizeof(Trie));
	g_root->is_end = false;
	for (int i = 0; i < 26; ++i) {
		g_root->next[i] = NULL;
	}
	for (int i = 0; i < products_size; ++i) {
		trie_insert(products[i]);
	}


	(*return_size) = strlen(search_word);
	ret = malloc((*return_size) * sizeof(char **));
	(*return_col_size) = malloc((*return_size) * sizeof(int));

	tmp = malloc(RET_TMP_SIZE * sizeof(char));

	Trie *search_node = g_root;

	for (int i = 0; i < (*return_size); ++i) {
		int c = search_word[i];
		int n = c + CHAR_OFFSET;

		if (search_node->next[n] == NULL) {
			for (; i < (*return_size); ++i) {
				(*return_col_size)[i] = 0;
			}
			break;
		}

		search_node = search_node->next[n];

		tmp[i] = c;
		tmp_base = i + 1;
		ret_p1 = i;
		ret_p2 = 0;

		ret[i] = malloc(3 * sizeof(char *));
		suggest(search_node, 0);

		(*return_col_size)[i] = ret_p2;
	}

	trie_clean(g_root);
	free(tmp);

	return ret;
}
