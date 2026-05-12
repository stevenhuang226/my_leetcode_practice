#include "shdstd.h"

#include <stdint.h>
#undef int64_t
#define int64_t long long

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
	int32_t key;
} HashNode;

typedef struct {
	int32_t size;
	int32_t def_key;
	int32_t step;

	HashNode data[];
} HashMap;

typedef struct {
	int *head;
	int *next;
	int *to;
	uint32_t count;
} AdjustList;

AdjustList *adjust_create(int size)
{
	AdjustList *adjust = malloc(sizeof(AdjustList));

	adjust->head = malloc(size * sizeof(int));
	adjust->next = malloc(size * 2 * sizeof(int));
	adjust->to = malloc(size * 2 * sizeof(int));
	adjust->count = 0;

	memset(adjust->head, 0xff, size * sizeof(int));

	return adjust;
}

void adjust_clean(AdjustList *adj)
{
	free(adj->head);
	free(adj->next);
	free(adj->to);
	free(adj);
}

static inline uint32_t hash(int32_t key, int32_t size)
{
	return key % size;
}

HashMap *hash_create(int32_t size, int32_t step)
{
	HashMap *map = malloc(sizeof(HashMap) + size * sizeof(HashNode));

	map->size = size;
	map->def_key = -1;	// force def key/val to -1. This can use memset to speed up
	map->step = step;

	memset(map->data, 0xff, size * sizeof(HashNode));

	return map;
}

int32_t hash_mapping(HashMap *map, int32_t key)
{
	int32_t hashed = hash(key, map->size);
	while (map->data[hashed].key != map->def_key) {
		if (map->data[hashed].key == key) {
			return hashed;
		}
		hashed = hash(hashed + map->step, map->size);
	}
	map->data[hashed].key = key;
	return hashed;
}

void adj_append(AdjustList *adj, uint32_t host, int value)
{
	adj->to[adj->count] = value;
	adj->next[adj->count] = adj->head[host];
	adj->head[host] = adj->count;
	++adj->count;
}

int64_t *distance(int *nums, int size, int *ret_size)
{
	int32_t exp_max = MIN(1e5 + 8, size * 2);

	AdjustList *adj = adjust_create(exp_max);
	HashMap *hm = hash_create(size * 2, 1);

	for (int i = 0; i < size; ++i) {
		uint32_t val = (uint32_t)nums[i];
		int32_t id = hash_mapping(hm, val);
		adj_append(adj, id, i);
	}

	int64_t *result = malloc(size * sizeof(int64_t));

	for (int i = 0; i < exp_max; ++i) {
		int tail = adj->head[i];
		int next = -1;
		if (tail < 0) {
			continue;
		}

		int left = 0;

		int tail_val = adj->to[tail];
		int64_t sum = 0;

		next = tail;
		while (next >= 0) {
			int curr = adj->to[next];
			next = adj->next[next];

			sum += (tail_val - curr);
			++left;
		}

		int right = 0;
		int prev = tail_val;
		next = tail;
		while (next >= 0) {
			int curr = adj->to[next];
			next = adj->next[next];

			int64_t gap = (prev - curr);
			prev = curr;

			sum += right * gap;
			sum -= left * gap;

			result[curr] = sum;

			--left;
			++right;
		}
	}

	free(hm);
	adjust_clean(adj);

	*ret_size = size;
	return result;
}
