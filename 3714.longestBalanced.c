#include "shdstd.h"

/*
 * auth: stevenhuang.dog@gmail.com
 * with chatgpt help
 */
#define INF32 (INT32_MAX / 4)
#define INF64 (INT64_MAX / 4)
#define NEG_INF32 -(INF32)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct {
	uint64_t key;
	int32_t value;
} HashItem;

typedef struct {
	HashItem *table;
	uint32_t capacity;

	int32_t def_val;
	uint64_t def_key;

	uint64_t step;
} HashMap;

static inline uint64_t encode(int32_t high, int32_t low)
{
	return ((uint64_t)(uint32_t)high << 32) | (uint32_t)low;
}

static inline uint64_t hash(uint64_t key, uint32_t size)
{
	return key % (uint64_t)size;
}

HashMap *hashMap_init(int32_t size, uint64_t def_key, int32_t def_val)
{
	HashMap *map = malloc(sizeof(HashMap));
	map->table = malloc(size * sizeof(HashItem));
	map->capacity = size;
	map->def_key = def_key;
	map->def_val = def_val;

	map->step = 7919; // a random number might make code faster on leetcode

	for (int i = 0; i < size; ++i) {
		map->table[i].key = def_key;
		map->table[i].value = def_val;
	}

	return map;
}

void hashMap_clean(HashMap *map)
{
	free(map->table);
	free(map);
}

int32_t hashMap_insert(HashMap *map, uint64_t key, int32_t value)
{
	uint64_t hashed = hash(key, map->capacity);
	while (map->table[hashed].key != map->def_key) {
		if (map->table[hashed].key == key) {
			return map->table[hashed].value;
		}
		hashed = hash(hashed + map->step, map->capacity);
	}
	map->table[hashed].key = key;
	map->table[hashed].value = value;
	return value;
}

int32_t hashMap_find(HashMap *map, uint64_t key)
{
	uint64_t hashed = hash(key, map->capacity);
	while (map->table[hashed].key != map->def_key) {
		if (map->table[hashed].key == key) {
			return map->table[hashed].value;
		}
		hashed = hash(hashed + map->step, map->capacity);
	}

	return -1;
}

int longestBalanced(char *s)
{
	int size = strlen(s);
	int offset = -'a';

	if (size == 1) {
		return 1;
	}

	int best_length = 0;

	int curr_run = 1;
	for (int i = 0; i < size-1; ++i) {
		if (s[i] == s[i+1]) {
			++curr_run;
		} else {
			curr_run = 1;
		}
		best_length = MAX(best_length, curr_run);
	}

	if (best_length > size / 2) {
		return best_length;
	}

	HashMap *abc_map = hashMap_init(size * 2, INF64, NEG_INF32);
	HashMap *ab_map = hashMap_init(size * 2, INF64, NEG_INF32);
	HashMap *bc_map = hashMap_init(size * 2, INF64, NEG_INF32);
	HashMap *ac_map = hashMap_init(size * 2, INF64, NEG_INF32);

	hashMap_insert(abc_map, encode(0, 0), -1);
	hashMap_insert(ab_map, encode(0, 0), -1);
	hashMap_insert(bc_map, encode(0, 0), -1);
	hashMap_insert(ac_map, encode(0, 0), -1);

	int prefix[3] = {0};

	for (int i = 0; i < size; ++i) {
		int c = s[i] + offset;
		++prefix[c];

		int pa = prefix[0], pb = prefix[1], pc = prefix[2];

		int last_abc = hashMap_insert(abc_map, encode(pa-pb, pb-pc), i);
		int last_ab = hashMap_insert(ab_map, encode(pa-pb, pc), i);
		int last_bc = hashMap_insert(bc_map, encode(pb-pc, pa), i);
		int last_ac = hashMap_insert(ac_map, encode(pa-pc, pb), i);

		if (last_abc < i) {
			best_length = MAX(best_length, i - last_abc);
		}
		if (last_ab < i) {
			best_length = MAX(best_length, i - last_ab);
		}
		if (last_bc < i) {
			best_length = MAX(best_length, i - last_bc);
		}
		if (last_ac < i) {
			best_length = MAX(best_length, i - last_ac);
		}
	}

	hashMap_clean(abc_map);
	hashMap_clean(ab_map);
	hashMap_clean(bc_map);
	hashMap_clean(ac_map);

	return best_length;
}
