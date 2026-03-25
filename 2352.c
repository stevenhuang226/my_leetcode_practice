#include "shdstd.h"

#define MOD 1000000007
#define MOD64 (INT64_MAX / 4 - 1)
#define ROLL_BASE 131

#define HASHMAP_SIZE 100004
#define HASHMAP_DEF_KEY 0
#define HASHMAP_DEF_VAL 0

typedef struct {
	uint64_t key;
	int value;
} Node;

typedef struct {
	Node *table;
	uint64_t size;
	uint64_t default_key;
	int default_value;
} HashMap;

uint64_t hash(uint64_t key, uint64_t size)
{
	return key % size;
}

HashMap *hash_create(uint64_t size, uint64_t default_key, int default_value)
{
	HashMap *map = malloc(sizeof(HashMap));
	map->table = malloc(size * sizeof(Node));
	map->size = size;
	for (int i = 0; i < size; ++i) {
		map->table[i].key = default_key;
		map->table[i].value = default_value;
	}
	map->default_key = default_key;
	map->default_value = default_value;
	return map;
}

void hash_insert(HashMap *map, uint64_t key, int value)
{
	Node *table = map->table;
	uint64_t default_key = map->default_key;
	uint64_t size = map->size;
	uint64_t index = hash(key, size);
	while (table[index].key != default_key) {
		if (table[index].key == key) {
			table[index].value = value;
			return;
		}
		index = hash(index + 1, size);
	}
	table[index].key = key;
	table[index].value = value;
	return;
}

void hash_append(HashMap *map, uint64_t key)
{
	Node *table = map->table;
	uint64_t default_key = map->default_key;
	uint64_t size = map->size;
	uint64_t index = hash(key, size);
	while (table[index].key != default_key) {
		if (table[index].key == key) {
			++table[index].value;
			return;
		}
		index = hash(index + 1, size);
	}
	table[index].key = key;
	++table[index].value;
	return;
}

int hash_find(HashMap *map, uint64_t key)
{
	Node *table = map->table;
	uint64_t size = map->size;
	uint64_t default_key = map->default_key;
	uint64_t index = hash(key, size);
	while (table[index].key != default_key) {
		if (table[index].key == key) {
			return table[index].value;
		}
		index = hash(index + 1, size);
	}
	return map->default_value;
}

void hash_free(HashMap *map)
{
	free(map->table);
	free(map);

	return;
}

int equalPairs(int **grid, int size, int *p_col_size)
{
	int base = ROLL_BASE;
	HashMap *map = hash_create(HASHMAP_SIZE, HASHMAP_DEF_KEY, HASHMAP_DEF_VAL);
	int count = 0;
	for (int i = 0; i < size; ++i) {
		uint64_t key = grid[0][i];
		for (int i2 = 1; i2 < size; ++i2) {
			key = (key * base + grid[i2][i]) % MOD64;
		}
		printf("hash append key:%d\n");
		hash_append(map, key);
	}
	for (int i = 0; i < size; ++i) {
		uint64_t key = grid[i][0];
		for (int i2 = 1; i2 < size; ++i2) {
			key = (key * base + grid[i][i2]) % MOD64;
		}
		int find = hash_find(map, key);
		count += find;
	}
	hash_free(map);
	return count;
}
