#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
	int key;
	int val;
} HashNode;

typedef struct {
	uint32_t capacity;
	uint32_t step;
	int def_key;
	int def_val;
	HashNode data[];
} HashMap;

uint32_t hash(int key, uint32_t size)
{
	return (uint32_t)key % size;
}

HashMap *hash_create(int size)
{
	HashMap *map = malloc(sizeof(HashMap) + size * sizeof(HashNode));

	map->def_key = 0;
	map->def_val = 0;

	memset(map->data, 0x00, size * sizeof(HashNode));

	map->capacity = size;
	map->step = 1;

	return map;
}

void hash_insert(HashMap *map, int key, int val)
{
	uint32_t hashed = hash(key, map->capacity);
	while (map->data[hashed].key != map->def_key) {
		if (map->data[hashed].key == key) {
			map->data[hashed].val = val;
		}
		hashed = hash(hashed + map->step, map->capacity);
	}
	map->data[hashed].key = key;
	map->data[hashed].val = val;
}

int hash_delta(HashMap *map, int key, int del)
{
	uint32_t hashed = hash(key, map->capacity);
	while (map->data[hashed].key != map->def_key) {
		if (map->data[hashed].key == key) {
			map->data[hashed].val += del;
			return map->data[hashed].val;
		}
		hashed = hash(hashed + map->step, map->capacity);
	}
	map->data[hashed].key = key;
	map->data[hashed].val = del;
	return map->data[hashed].val;
}

int hash_search(HashMap *map, int key)
{
	uint32_t hashed = hash(key, map->capacity);
	while (map->data[hashed].key != map->def_key) {
		if (map->data[hashed].key == key) {
			return map->data[hashed].val;
		}
		hashed = hash(hashed + map->step, map->capacity);
	}

	return map->def_val;
}

int maximumLength(int *nums, int size)
{
	int exp_max;
	int64_t qlim = 1e4;
	int64_t lim = 1e9;

	for (int i = 0; i < size; ++i) {
		exp_max = MAX(exp_max, nums[i]);
	}
	exp_max = MIN(size * 8, exp_max);

	HashMap *hashmap = hash_create(exp_max);

	int *dist = malloc(size * sizeof(int));
	int dp = 0;

	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		int curr_count = hash_delta(hashmap, num, 1);
		if (num > 1 && num < qlim && curr_count == 1) {
			dist[dp++] = num;
		}
	}

	int best = 0;

	int one_count = hash_search(hashmap, 1);
	int one_length = one_count - (one_count % 2 == 0);

	best = MAX(best, one_length);

	for (int i = 0; i < dp; ++i) {
		int64_t base = dist[i];

		int length = 0;
		while (hash_search(hashmap, base) >= 2) {
			length += 2;
			base *= base;
			if (base > lim) {
				break;
			}
		}
		if (hash_search(hashmap, base) >= 1) {
			length += 1;
		} else {
			length -= 1;
		}

		best = MAX(best, length);
	}

	free(hashmap);
	free(dist);

	return best;
}
