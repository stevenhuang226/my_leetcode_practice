#include "shdstd.h"

#define CHAR_OFFSET (-('a'))

typedef struct Trie Trie;

struct Trie{
	Trie *trie[26];
	bool is_end;
};

Trie *trieCreate()
{
	Trie *obj = malloc(sizeof(Trie));
	for (int i = 0; i < 26; ++i) {
		obj->trie[i] = NULL;
	}
	obj->is_end = false;
	return obj;
}

void trieInsert(Trie *obj, char *word)
{
	Trie *curr_trie = obj;

	char c;
	int ptr = 0;
	while ((c = word[ptr++]) != '\0') {
		int n = c + CHAR_OFFSET;

		if (curr_trie->trie[n] != NULL) {
			curr_trie = curr_trie->trie[n];
			continue;
		}

		curr_trie->trie[n] = malloc(sizeof(Trie));
		curr_trie->trie[n]->is_end = false;
		for (int i = 0; i < 26; ++i) {
			curr_trie->trie[n]->trie[i] = NULL;
		}
		curr_trie = curr_trie->trie[n];
	}
	curr_trie->is_end = true;
	return;
}

bool trieSearch(Trie *obj, char *word)
{
	Trie *curr_trie = obj;

	char c;
	int ptr = 0;
	while ((c = word[ptr++]) != '\0') {
		int n = c + CHAR_OFFSET;

		if (curr_trie->trie[n] == NULL) {
			return false;
		}

		curr_trie = curr_trie->trie[n];
	}

	if (curr_trie->is_end) {
		return true;
	} else {
		return false;
	}
}

bool trieStartsWith(Trie *obj, char *word)
{
	Trie *curr_trie = obj;

	char c;
	int ptr = 0;
	while ((c = word[ptr++]) != '\0') {
		int n = c + CHAR_OFFSET;

		if (curr_trie->trie[n] == NULL) {
			return false;
		}

		curr_trie = curr_trie->trie[n];
	}
	return true;
}

void trie_free_ch(Trie *obj)
{
	for (int i = 0; i < 26; ++i) {
		if (obj->trie[i] != NULL) {
			trie_free_ch(obj->trie[i]);
		}
	}
	free(obj);
	return;
}

void trieFree(Trie *obj)
{
	trie_free_ch(obj);
	return;
}
