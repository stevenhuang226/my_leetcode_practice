#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>

#define HASH_TABLE_SIZE 10007
#define MAX_STR_SIZE 101

#define DBFS_QUENE_SIZE 2000

typedef struct Hash_node {
	char key[MAX_STR_SIZE];
	struct Hash_node *next;
} Hash_node;

Hash_node **table;

uint64_t hash(const char *str)
{
	uint64_t h = 5381;
	int c;
	for (; c = *str++; ) {
		h = ((h << 5) + h) + c;
	}
	return h % HASH_TABLE_SIZE;
}

int8_t find(const char *key, int size)
{
	uint64_t hashed = hash(key);
	Hash_node *node;
	for (node = table[hashed]; node != NULL; node = node->next) {
		if (strncmp(node->key, key, size) == 0)	return 1;
	}
	return 0;
}

int8_t insert(const char *key, int size)
{
	uint64_t hashed = hash(key);
	Hash_node *node = malloc(sizeof(Hash_node));
	memcpy(node->key, key, size);
	node->next = table[hashed]; /* point to old head */
	table[hashed] = node; /* change old to new head */
	return 0;
}
char* findLexSmallestString(char* s, int a, int b)
{
	int i;
	int str_size = strlen(s);
	int boffset = b % str_size;

	char *presently;
	presently = malloc(DBFS_QUENE_SIZE * str_size * sizeof(char));
	int pre_ptr = 0;
	char *next_bfr;
	next_bfr = malloc(DBFS_QUENE_SIZE * str_size * sizeof(char));
	int next_ptr = 0;

	table = calloc(HASH_TABLE_SIZE, sizeof(Hash_node *));


	memcpy(&presently[pre_ptr], s, str_size);

	char smallest[str_size+1];
	memcpy(smallest, s, str_size);

	for (;pre_ptr >= 0; ) {
		for (; pre_ptr >= 0; pre_ptr -= str_size) {
			char proca[MAX_STR_SIZE];
			char procb[2 * MAX_STR_SIZE];
			memcpy(proca, &presently[pre_ptr], str_size);
			memcpy(&procb[0 + boffset], &presently[pre_ptr], str_size);

			if (strncmp(proca, smallest, str_size) < 0) {
				memcpy(smallest, proca, str_size);
			}
			for (i = 1; i < str_size; i+=2) {
				proca[i] = ((proca[i] - '0' + a) % 10) + '0';
			}
			if (! find(proca, str_size)) {
				insert(proca, str_size);
				memcpy(&next_bfr[next_ptr], proca, str_size);
				next_ptr+=str_size;
			}
			
			memcpy(procb, &procb[str_size], boffset);
			if (! find(procb, str_size)) {
				insert(procb, str_size);
				memcpy(&next_bfr[next_ptr], procb, str_size);
				next_ptr+=str_size;
			}
		}
		char *tmp = presently;

		presently = next_bfr;
		pre_ptr = next_ptr - str_size;

		next_bfr = tmp;
		next_ptr = 0;
	}

	char *res = malloc((str_size + 1) * sizeof(char));
	memcpy(res, smallest, str_size);
	res[str_size] = '\0';

	return res;
}
