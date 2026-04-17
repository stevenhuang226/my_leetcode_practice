#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
	uint32_t key;
	int value;
} HashNode;

typedef struct {
	uint32_t size;
	uint32_t step;

	uint32_t def_key;
	int32_t def_value;

	HashNode data[];
} HashTable;

static inline uint32_t hash(uint32_t key, uint32_t size)
{
	return key % size;
}

HashTable *hash_create(uint32_t size, uint32_t step,
	uint32_t def_key, int32_t def_value)
{
	HashTable *table = malloc(sizeof(HashTable) +
		size * sizeof(HashNode));

	for (int i = 0; i < size; ++i) {
		table->data[i].key = def_key;
		table->data[i].value = def_value;
	}

	table->def_key = def_key;
	table->def_value = def_value;
	table->size = size;
	table->step = step;

	return table;
};

void hash_write(HashTable *table, uint32_t key, int value)
{
	uint32_t hashed = hash(key, table->size);

	while (table->data[hashed].key != table->def_key) {
		if (table->data[hashed].key == key) {
			table->data[hashed].value = value;
			return;
		}

		hashed = hash(hashed + table->step, table->size);
	}
	table->data[hashed].key = key;
	table->data[hashed].value = value;
}

int hash_search(HashTable *table, uint32_t key)
{
	uint32_t hashed = hash(key, table->size);

	while (table->data[hashed].key != table->def_key) {
		if (table->data[hashed].key == key) {
			return table->data[hashed].value;
		}
		hashed = hash(hashed + table->step, table->size);
	}
	return table->def_value;
}

int reverse(int num)
{
	int res = 0;
	while (num) {
		res *= 10;
		res += num % 10;
		num = num / 10;
	}
	return res;
}

int minMirrorPairDistance(int *nums, int size)
{
	int exp_max = size * 2;

	HashTable *prev_hash = hash_create(exp_max, 1, INT32_MAX, -1);

	int best = INT32_MAX;
	for (int i = 0; i < size; ++i) {
		int num = nums[i];

		int prev = hash_search(prev_hash, (uint32_t)num);
		if (prev >= 0) {
			best = MIN(best, i - prev);
		}

		int pair = reverse(num);
		hash_write(prev_hash, pair, i);
	}

	free(prev_hash);

	if (best == INT32_MAX) {
		return -1;
	}
	return best;
}
