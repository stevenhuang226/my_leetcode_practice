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

	int c;
	int ptr = 0;
	while ((c = word[ptr++]) != '\0') {
		c += CHAR_OFFSET;

		if (trie->next[c]) {
			trie = trie->next[c];
			continue;
		}

		trie->next[c] = malloc(sizeof(Trie));
		trie->next[c]->is_end = false;

		for (int i = 0; i < 26; ++i) {
			trie->next[c]->next[i] = NULL;
		}

		trie = trie->next[c];
	}
	trie->is_end = true;
	return;
}

static char tmp[RET_TMP_SIZE];
int tmp_base;

char ***ret;
int ret_l1;
int ret_l2;

void cpy2ret(int offset)
{
	tmp[tmp_base + offset] = '\0';
	ret[ret_l1][ret_l2] = malloc((tmp_base + offset + 1) * sizeof(char));
	strcpy(ret[ret_l1][ret_l2], tmp);
	++ret_l2;
	return;
}

void suggest(Trie *node, int offset)
{
	if (ret_l2 >= 3) {
		return;
	}
	if (node->is_end) {
		cpy2ret(offset);
	}

	for (int i = 0; i < 26; ++i) {
		if (node->next[i] == NULL) {
			continue;
		}
		tmp[tmp_base + offset] = i - CHAR_OFFSET;
		suggest(node->next[i], offset + 1);
		if (ret_l2 >= 3) break;
	}
	return;
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


	int ret_size = strlen(search_word);

	ret = malloc(ret_size * sizeof(char **));

	Trie *search_node = g_root;

	(*return_col_size) = malloc(ret_size * sizeof(int));

	for (int i = 0; i < ret_size; ++i) {
		int c = search_word[i];
		int n = c + CHAR_OFFSET;

		if (search_node->next[n] == NULL) {
			(*return_col_size)[i] = 0;
			continue;
		}

		ret[i] = malloc(3 * sizeof(char *));

		search_node = search_node->next[n];

		tmp[i] = c;

		tmp_base = i;

		ret_l1 = i;
		ret_l2 = 0;

		suggest(search_node, 1);

		(*return_col_size)[i] = ret_l2;
	}

	(*return_size) = ret_size;

	trie_clean(g_root);

	return ret;
}
