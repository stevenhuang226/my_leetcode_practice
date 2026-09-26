#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
	char *key_ptr;
	char *val_ptr;
} SHashNode;

typedef struct {
	uint32_t capacity;
	uint32_t step;
	SHashNode def;

	SHashNode data[];
} SHashMap;

uint64_t hash_chars(const char *s)
{
	uint64_t hash = 0;

	while (*s) {
		hash = hash * 31 + (uint8_t)*s;
		++s;
	}

	return hash;
}

uint32_t hash_u64(uint64_t k, uint32_t sz)
{
	return (uint32_t)(k % sz);
}

SHashMap *hash_create(size_t capacity)
{
	SHashMap *smap = malloc(sizeof(SHashMap) + capacity * sizeof(SHashNode));
	smap->def.key_ptr = NULL;
	smap->def.val_ptr = "?";
	smap->step = 1;
	smap->capacity = capacity;
	memset(smap->data, 0x00, capacity * sizeof(SHashNode));

	return smap;
}

void hash_insert(SHashMap *smap, char *key, char *val)
{
	uint32_t h = hash_u64(hash_chars(key), smap->capacity);
	while (smap->data[h].key_ptr != smap->def.key_ptr) {
		if (smap->data[h].key_ptr == key)
			return;
		h = hash_u64(h + smap->step, smap->capacity);
	}

	smap->data[h].key_ptr = key;
	smap->data[h].val_ptr = val;
}

char *hash_search(SHashMap *smap, char *key)
{
	uint32_t h = hash_u64(hash_chars(key), smap->capacity);
	while (smap->data[h].key_ptr != smap->def.key_ptr) {
		if (strcmp(smap->data[h].key_ptr, key) == 0) {
			return smap->data[h].val_ptr;
		}

		h = hash_u64(h + smap->step, smap->capacity);
	}

	return smap->def.val_ptr;
}

char *evaluate(char *s, char ***knowledge, int k_size, int *k_col_size)
{
	int expsz = MIN(k_size * 3, 1e5 + 8);
	expsz = MAX(10, expsz);

	SHashMap *smap = hash_create(expsz);

	for (int i = 0; i < k_size; ++i) {
		hash_insert(smap, knowledge[i][0], knowledge[i][1]);
	}

	char *res = malloc((int)(1e5 + 8) * sizeof(char));
	char tmp[20];
	size_t r = 0;
	while (*s) {
		if (*s != '(') {
			res[r++] = *s;
			++s;
			continue;
		}

		char *head = ++s;
		while (*s != ')') {
			++s;
		}
		*s = '\0';
		char *v = hash_search(smap, head);
		while (*v) {
			res[r++] = *v;
			++v;
		}
		*s = ')';

		++s;
	}

	res[r++] = '\0';

	free(smap);

	return res;
}
