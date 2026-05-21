#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
typedef struct {
	int key;
} HashNode;

typedef struct {
	int size;
	int def_key;
	int step;

	HashNode data[];
} HashMap;

static inline uint32_t hash(int key, uint32_t size)
{
	return ((uint32_t)key) % size;
}

void hash_create(HashMap *map, int key)
{
	uint32_t hashed = hash(key, map->size);

	while (map->data[hashed].key != map->def_key) {
		if (map->data[hashed].key == key) {
			return;
		}
		hashed = hash(hashed + map->step, map->size);
	}
	map->data[hashed].key = key;
}

int8_t hash_exist(HashMap *map, int key)
{
	uint32_t hashed = hash(key, map->size);

	while (map->data[hashed].key != map->def_key) {
		if (map->data[hashed].key == key) {
			return true;
		}
		hashed = hash(hashed + map->step, map->size);
	}
	return false;
}

#define REV_MAX 10
int longestCommonPrefix(int *arra, int sizea, int *arrb, int sizeb)
{
	int exp_max = 0;
	for (int i = 0; i < sizea; ++i) {
		exp_max = MAX(exp_max, arra[i]);
	}
	exp_max = MIN(exp_max + 8, 1e5 + 8);

	int hash_size = exp_max;
	HashMap *hashmap = calloc(1, sizeof(HashMap) + hash_size * sizeof(HashNode));
	hashmap->size = hash_size;
	hashmap->def_key = 0;
	hashmap->step = 1003;

	int rev[REV_MAX];
	int r = 0;
	for (int i = 0; i < sizea; ++i) {
		int num = arra[i];
		while (num) {
			rev[r++] = num % 10;
			num /= 10;
		}

		int d = 0;
		while (r) {
			d = d * 10 + rev[--r];
			hash_create(hashmap, d);
		}
	}

	int best = 0;
	for (int i = 0; i < sizeb; ++i) {
		int num = arrb[i];
		r = 0;
		while (num) {
			rev[r++] = num % 10;
			num /= 10;
		}

		int d = 0;
		int common = 0;
		while (r) {
			d = d * 10 + rev[--r];
			if (!hash_exist(hashmap, d)) break;

			++common;
			best = MAX(best, common);
		}
	}

	free(hashmap);
	return best;
}
