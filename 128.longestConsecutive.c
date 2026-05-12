#include "shdstd.h"

#define INF32 (INT32_MAX / 4)
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define NEG_INF32 -(INF32)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct {
	int key;
	int val;
} HashNode;

typedef struct {
	uint32_t size;
	uint32_t step;
	int def_key;
	int def_val;
	HashNode table[];
} HashMap;

HashMap* HashMapCreate(int size, int def_key, int def_val, uint32_t step)
{
	HashMap* map = malloc(sizeof(HashMap) + size * sizeof(HashNode));
	for (int i = 0; i < size; ++i) {
		map->table[i].key = def_key;
		map->table[i].val = def_val;
	}
	map->size = size;
	map->step = step;
	map->def_key = def_key;
	map->def_val = def_val;
	return map;
}

uint32_t hash(int key, uint32_t size)
{
	return (uint32_t)key % size;
}

void HashMapAddOne(HashMap* map, int key)
{
	uint32_t hashed = hash(key, map->size);
	while (map->table[hashed].key != map->def_key) {
		if (map->table[hashed].key == key) {
			++map->table[hashed].val;
			return;
		}
		hashed = hash(hashed + map->step, map->size);
	}

	map->table[hashed].key = key;
	map->table[hashed].val = 1;
}

int HashMapSearchAndClean(HashMap* map, int key)
{
	uint32_t hashed = hash(key, map->size);
	while (map->table[hashed].key != map->def_key) {
		if (map->table[hashed].key == key) {
			int res = map->table[hashed].val;
			map->table[hashed].val = map->def_val;
			return res;
		}
		hashed = hash(hashed + map->step, map->size);
	}

	return map->def_val;
}

int longestConsecutive(int* nums, int size)
{
	int exp_max = size * 3;
	HashMap* map = HashMapCreate(exp_max, NEG_INF32, 0, 1003);

	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		HashMapAddOne(map, num);
	}

	int best = 0;

	for (int i = 0; i < exp_max; ++i) {
		if (map->table[i].val <= 0) continue;

		int curr = map->table[i].key;

		int low = 0;
		while (HashMapSearchAndClean(map, curr - low - 1)) {
			++low;
		}

		int high = 0;
		while (HashMapSearchAndClean(map, curr + high + 1)) {
			++high;
		}

		int consecutive = low + high + 1;
		best = MAX(best, consecutive);
	}

	free(map);

	return best;
}
