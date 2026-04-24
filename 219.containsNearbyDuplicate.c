#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
typedef struct {
	int key;
	int val;
} HashNode;

typedef struct {
	int size;
	int def_key;
	int def_val;
	int step;
	HashNode data[];
} HashTable;

HashTable *hash_create(int size, int step)
{
	HashTable *table = malloc(sizeof(HashTable) + size * sizeof(HashNode));

	table->def_key = INT32_MIN;
	table->def_val = -1;
	table->step = step;
	table->size = size;

	for (int i = 0; i < size; ++i) {
		table->data[i].key = INT32_MIN;
		table->data[i].val = -1;
	}

	return table;
}

static inline uint32_t hash(int key, int size)
{
	return (uint32_t)key % (uint32_t)size;
}

void hash_insert(HashTable *table, int key, int val)
{
	uint32_t hashed = hash(key, table->size);
	while (table->data[hashed].key != table->def_key) {
		if (table->data[hashed].key == key) {
			table->data[hashed].val = val;
			return;
		}
		hashed = hash(hashed + table->step, table->size);
	}
	table->data[hashed].key = key;
	table->data[hashed].val = val;
}

int hash_search(HashTable *table, int key)
{
	uint32_t hashed = hash(key, table->size);
	while (table->data[hashed].key != table->def_key) {
		if (table->data[hashed].key == key) {
			return table->data[hashed].val;
		}
		hashed = hash(hashed + table->step, table->size);
	}
	return table->def_val;
}

bool containsNearbyDuplicate(int *nums, int size, int k)
{
	int exp_max = MIN(1e5 + 8, size * 2);
	HashTable *prev = hash_create(exp_max, 1003);

	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		int p = hash_search(prev, num);
		if (p >= 0) {
			if (i - p <= k) {
				free(prev);
				return true;
			}
		}
		hash_insert(prev, num, i);
	}

	free(prev);
	return false;
}
