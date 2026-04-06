#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define INF32 (INT32_MAX / 4)
typedef struct {
	uint32_t key;
} HashNode;

typedef struct {
	uint32_t capacity;
	int step;

	uint32_t def_key;
	HashNode data[];
} HashTable;

HashTable *create_table(uint32_t size, int step, uint32_t def_key)
{
	HashTable *table = malloc(sizeof(HashTable) + size * sizeof(HashNode));
	table->capacity = size;
	table->step = step;
	table->def_key = def_key;

	for (int i = 0; i < size; ++i) {
		table->data[i].key = def_key;
	}

	return table;
}

static inline uint32_t hash(uint32_t key, uint32_t capacity)
{
	return key % capacity;
}

int8_t hash_insert(HashTable *table, uint32_t key)
{
	uint32_t hashed = hash(key, table->capacity);
	while (table->data[hashed].key != table->def_key) {
		if (table->data[hashed].key == key) {
			return 0;
		}
		hashed = hash(hashed + table->step, table->capacity);
	}
	table->data[hashed].key = key;
	return 0;
}

int8_t hash_exists(HashTable *table, uint32_t key)
{
	uint32_t hashed = hash(key, table->capacity);
	while (table->data[hashed].key != table->def_key) {
		if (table->data[hashed].key == key) {
			return true;
		}
		hashed = hash(hashed + table->step, table->capacity);
	}
	return false;
}

int offset = 3e4 + 8;
static inline uint32_t encode(int x, int y)
{
	x += offset;
	y += offset;

	return (uint32_t)x * ((uint32_t)6e4 + 16) + (uint32_t)y;
}

int robotSim(int *commands, int cmds_size,
	int **obstacles, int obstacles_size, int *obstacles_col_size)
{
	HashTable *table = create_table((uint32_t)(1e5 + 8), 3001, INF32);

	for (int i = 0; i < obstacles_size; ++i) {
		int x = obstacles[i][0];
		int y = obstacles[i][1];
		hash_insert(table, encode(x, y));
	}

	int best = 0;

	int dir_x = 0;
	int dir_y = 1;

	int curr_x = 0;
	int curr_y = 0;

	for (int i = 0; i < cmds_size; ++i) {
		int code = commands[i];

		if (code == -2) {
			int new_x = -(dir_y);
			int new_y = dir_x;
			dir_x = new_x;
			dir_y = new_y;
			continue;
		}
		if (code == -1) {
			int new_x = dir_y;
			int new_y = -(dir_x);
			dir_x = new_x;
			dir_y = new_y;
			continue;
		}

		for (int i = 0; i < code; ++i) {
			int new_x = curr_x + dir_x;
			int new_y = curr_y + dir_y;

			/* check new_x new_y is obstacle */
			if (hash_exists(table, encode(new_x, new_y))) {
				break;
			} else {
				curr_x = new_x;
				curr_y = new_y;
			}

			int new = curr_x * curr_x + curr_y * curr_y;
			best = MAX(best, new);
		}
	}

	free(table);

	return best;
}
