#include "shdstd.h"

#define MOD 1000000007
#define INF64 (INT64_MAX / 4)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
	uint64_t key;
} Hash_entry;

typedef struct {
	Hash_entry *buckets;
	uint32_t size;
	uint32_t capacity;

	uint64_t default_key;
} Hash_table;

uint64_t hash_table_hash(int64_t value, uint32_t size)
{
	return (uint64_t)value % (uint64_t)size;
}

int8_t hash_table_insert(Hash_table *table, int64_t key)
{
	Hash_entry *buckets = table->buckets;
	uint64_t hash = hash_table_hash(key, table->capacity);
	while (buckets[hash].key != table->default_key) {
		if (buckets[hash].key == key) {
			return 1;
		}
		hash = hash_table_hash(hash + 1, table->capacity);
	}
	buckets[hash].key = key;
	return 0;
}

int8_t hash_table_find(Hash_table *table, int64_t key)
{
	Hash_entry *buckets = table->buckets;
	uint64_t hash = hash_table_hash(key, table->capacity);
	while (buckets[hash].key != table->default_key) {
		if (buckets[hash].key == key) {
			return true;
		}
		hash = hash_table_hash(hash + 1, table->capacity);
	}
	return false;
}

Hash_table *hash_table_create(uint32_t capacity, uint64_t default_key)
{
	Hash_table *table = malloc(sizeof(Hash_table));
	table->capacity = capacity;
	table->default_key = default_key;
	table->buckets = malloc(capacity * sizeof(Hash_entry));
	for (int i = 0; i < capacity; ++i) {
		table->buckets[i].key = default_key;
	}
	table->size = 0;
	return table;
}

int cmp32(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int maximizeSquareArea(int m, int n, int *h_fences, int h_size, int *v_fences, int v_size)
{
	int *h = malloc((h_size + 2) * sizeof(int));
	memcpy(h, h_fences, h_size * sizeof(int));
	h[h_size++] = 1;
	h[h_size++] = m;

	int *v = malloc((v_size + 2) * sizeof(int));
	memcpy(v, v_fences, v_size * sizeof(int));
	v[v_size++] = 1;
	v[v_size++] = n;

	qsort(h, h_size, sizeof(int), cmp32);
	qsort(v, v_size, sizeof(int), cmp32);

	uint32_t table_capacity = 246793; // random prime I got on Internet. And it get ~750ms
	Hash_table *table = hash_table_create(table_capacity, INF64);

	for (int i = 0; i < h_size; ++i) {
		for (int i2 = i + 1; i2 < h_size; ++i2) {
			hash_table_insert(table, h[i2] - h[i]);
		}
	}

	int64_t max_size = -1;

	for (int i = 0; i < v_size; ++i) {
		for (int i2 = i + 1; i2 < v_size; ++i2) {
			int64_t size = v[i2] - v[i];
			if (hash_table_find(table, size)) {
				max_size = MAX(max_size, size);
			}
		}
	}

	free(h);
	free(v);

	free(table->buckets);
	free(table);

	if (max_size < 0) {
		return -1;
	}

	int64_t res = (max_size * max_size) % MOD;

	return (int)res;
}
