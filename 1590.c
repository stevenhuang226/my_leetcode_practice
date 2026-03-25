#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define HASH(x, y) ((x) % (y))

#define NODE_DEFAULT_KEY -8
#define INF 100000000

typedef struct {
	int64_t key;
	int32_t val;
} Node;

typedef struct {
	Node *table;
	int32_t size;
} Hash_Map;

void hash_insert(Hash_Map *map, int64_t key, int value)
{
	Node *table = map->table;
	int32_t size = map->size;
	int32_t hashed = HASH(key, size);
	while (table[hashed].key != NODE_DEFAULT_KEY) {
		if (table[hashed].key == key) {
			table[hashed].val = value;
			return;
		}
		hashed = HASH(hashed+1, size);
	}
	table[hashed].key = key;
	table[hashed].val = value;
	return;
}

int32_t hash_find(Hash_Map *map, uint64_t key)
{
	Node *table = map->table;
	int32_t size = map->size;
	int32_t hashed = HASH(key, size);
	while (table[hashed].key != NODE_DEFAULT_KEY) {
		if (table[hashed].key == key) {
			return table[hashed].val;
		}
		hashed = HASH(hashed+1, size);
	}
	return NODE_DEFAULT_KEY;
}

Hash_Map *create_hash_map(int size)
{
	Hash_Map *map = malloc(sizeof(Hash_Map));
	map->size = size;
	map->table = malloc(map->size * sizeof(Node));
	int i;
	for (i = 0; i < map->size; ++i) {
		map->table[i].key = NODE_DEFAULT_KEY;
	}
	return map;
}

void hash_map_free(Hash_Map *map) {
	free(map->table);
	free(map);

	return;
}

int minSubarray(int *nums, int size, int p)
{
	int i;


	Hash_Map *hash_map = create_hash_map(size * 2);
	hash_insert(hash_map, 0, -1);

	uint64_t total_sum = 0;
	for (i = 0; i < size; ++i) {
		total_sum += nums[i];
	}

	int total_mod = total_sum % p;
	if (total_mod == 0) {
		return 0;
	}

	int32_t min = INF;
	uint32_t mod_prefix = 0;
	for (i = 0; i < size; ++i) {
		mod_prefix = (mod_prefix + nums[i]) % p;
		uint32_t curr_mod = mod_prefix;
		/* come from "(curr_mod + before) % p == total_mod" */
		uint32_t before = (curr_mod - total_mod + p) % p;
		int32_t pos = hash_find(hash_map, before);
		if (pos != NODE_DEFAULT_KEY) {
			int len = i - pos;
			min = MIN(min, len);
		}
		hash_insert(hash_map, curr_mod, i);
	}

	hash_map_free(hash_map);

	if (min == INF || min == size) {
		return -1;
	}

	return min;
}

int main()
{
	/*
	int nums[] = {8,32,31,18,34,20,21,13,1,27,23,22,11,15,30,4,2};
	int size = sizeof(nums) / sizeof(nums[0]);
	int p = 148;
	*/

	int nums[] = {6,3,5,2};
	int size = sizeof(nums) / sizeof(nums[0]);
	int p = 9;


	int res = minSubarray(nums, size, p);

	printf("%d\n", res);

	return 0;
}
