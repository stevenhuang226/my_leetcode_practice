#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

#define HASHMAP_LIMIT 100004

typedef struct {
	uint32_t key;
	int value;
} Node;

typedef struct {
	Node *table;
	uint32_t default_key;
	int default_value;
	uint32_t size;
} Map;

uint32_t hash(uint32_t key, uint32_t hash)
{
	return (uint32_t)(key % hash);
}

int8_t map_insert(Map *map, uint32_t key, int value)
{
	uint32_t hashed = hash(key, map->size);
	Node *table = map->table;
	uint32_t default_key = map->default_key;
	while (table[hashed].key != default_key) {
		if (table[hashed].key == key) {
			table[hashed].value = value;
			return 0;
		}
		hashed = hash(hashed + 1, map->size);
	}
	table[hashed].key = key;
	table[hashed].value = value;
	return 0;
}

int8_t map_append(Map *map, uint32_t key)
{
	uint32_t hashed = hash(key, map->size);
	Node *table = map->table;
	uint32_t default_key = map->default_key;
	while (table[hashed].key != default_key) {
		if (table[hashed].key == key) {
			++table[hashed].value;
			return 0;
		}
		hashed = hash(hashed + 1, map->size);
	}
	table[hashed].key = key;
	++table[hashed].value;
	return 0;
}

int map_find(Map *map, uint32_t key)
{
	uint32_t hashed = hash(key, map->size);
	Node *table = map->table;
	while (table[hashed].key != map->default_key) {
		if (table[hashed].key == key) {
			return table[hashed].value;
		}
		hashed = hash(hashed + 1, map->size);
	}
	return map->default_value;
}

Map *map_create(uint32_t table_max_size, uint32_t default_key, int default_value)
{
	Map *map = malloc(sizeof(Map));

	map->size = table_max_size;
	map->default_key = default_key;
	map->default_value = default_value;
	map->table = malloc(table_max_size * sizeof(Node));

	int i;
	for (i = 0; i < table_max_size; ++i) {
		map->table[i].key = default_key;
		map->table[i].value = default_value;
	}

	return map;
}

void map_free(Map *map)
{
	free(map->table);
	free(map);

	return;
}


int maxOperations(int *nums, int size, int k)
{
	uint32_t table_size = MIN(HASHMAP_LIMIT, k + 1);
	uint32_t default_key = 0;
	int default_value = 0;
	Map *map = map_create(table_size, default_key, default_value);

	int i;
	for (i = 0; i < size; ++i) {
		uint32_t key = nums[i];
		if (key >= k) continue;
		map_append(map, key);
	}

	int count = 0;

	for (i = 0; i < map->size; ++i) {
		if (map->table[i].value == 0) {
			continue;
		}

		uint32_t l_key = map->table[i].key;
		uint32_t r_key = k - l_key;

		if (l_key == r_key) {
			continue;
		}

		int l_val = map_find(map, l_key);
		int r_val = map_find(map, r_key);
		count += MIN(l_val, r_val);
	}

	if (k % 2 == 0) {
		uint32_t trg = k / 2;
		int val = map_find(map, trg);
		count += val;
	}

	map_free(map);

	return count / 2;
}

int main()
{
	int nums[] = {3,1,3,4,3};
	int size = sizeof(nums) / sizeof(nums[0]);
	int k = 5;

	int res = maxOperations(nums, size, k);
	printf("%d\n", res);

	return 0;
}
