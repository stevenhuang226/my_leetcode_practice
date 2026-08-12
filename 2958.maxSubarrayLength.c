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
	HashNode def;
	HashNode data[];
} HashTable;

HashTable *ht_create(int capacity, int step)
{
	HashTable *table = malloc(sizeof(HashTable) + capacity * sizeof(HashNode));
	table->def.key = -1;
	table->def.val = -1;
	memset(table->data, 0xff, capacity * sizeof(HashNode));
	table->capacity = capacity;
	table->step = step;
	return table;
}

uint32_t hash(int key, uint32_t capacity)
{
	return key % capacity;
}

int8_t ht_try(HashTable *table, int key, int adj, int lim)
{
	if (adj > lim)
		return false;
	uint32_t hashed = hash(key, table->capacity);
	while (table->data[hashed].key != table->def.key) {
		if (table->data[hashed].key == key) {
			if (table->data[hashed].val + adj > lim)
				return false;
			table->data[hashed].val += adj;
			return true;
		}
		hashed = hash(hashed + table->step, table->capacity);
	}
	table->data[hashed].key = key;
	table->data[hashed].val = adj;
	return true;
}

int maxSubarrayLength(int *nums, int size, int k)
{
	int exp_max = 0;
	for (int i = 0; i < size; ++i) {
		exp_max = MAX(exp_max, nums[i]);
	}

	exp_max = MAX(size, exp_max+8);
	exp_max = MIN((int)1e5 + 8, exp_max);

	HashTable *table = ht_create(exp_max, 1);


	int best = 0;
	int right = 0;
	for (int left = 0; left < size; ++left) {
		while (right < size && ht_try(table, nums[right], 1, k)) {
			++right;
		}

		best = MAX(best, right-left);
		ht_try(table, nums[left], -1, k);
	}

	free(table);

	return best;
}
