#include "shdstd.h"

#define MOD 1e9 + 7
#define DEF_CAPA 1e5 + 8

int mod = MOD;

enum OPERATION_TYPE {
	MULT,
	ADD
};

typedef struct {
	int32_t last_update;
	int value;
} Item;

typedef struct {
	int8_t type;
	int num;
} Operation;

typedef struct {
	Item *sequence;
	int32_t capacity;
	int32_t size;

	Operation *operations;
	int32_t operation_capacity;
	int32_t operation_size;
} Fancy;

Fancy *fancyCreate()
{
	Fancy *fancy = malloc(sizeof(Fancy));

	int def_size = DEF_CAPA;

	fancy->sequence = malloc(def_size * sizeof(Item));
	fancy->capacity = def_size;
	fancy->size = 0;

	fancy->operations = malloc(def_size * sizeof(Operation));
	fancy->operation_capacity = def_size;
	fancy->operation_size = 0;

	return fancy;
}

void fancyAppend(Fancy *fancy, int value)
{
	if (fancy->size >= fancy->capacity) return;

	fancy->sequence[fancy->size].last_update = fancy->operation_size;
	fancy->sequence[fancy->size].value = value;

	++fancy->size;
}

void fancyAddAll(Fancy *fancy, int inc)
{
	if (fancy->operation_size >= fancy->operation_capacity) return;

	fancy->operations[fancy->operation_size].type = ADD;
	fancy->operations[fancy->operation_size].num = inc;

	++fancy->operation_size;
}

void fancyMultAll(Fancy *fancy, int mult)
{
	if (fancy->operation_size >= fancy->operation_capacity) return;

	fancy->operations[fancy->operation_size].type = MULT;
	fancy->operations[fancy->operation_size].num = mult;

	++fancy->operation_size;
}

int fancyGetIndex(Fancy *fancy, int index)
{
	if (index >= fancy->size) {
		return -1;
	}

	int last_update = fancy->sequence[index].last_update;
	int curr_update = fancy->operation_size;
	int curr_value = fancy->sequence[index].value;

	if (last_update == curr_update) {
		return curr_value;
	}

	for (int i = last_update; i < curr_update; ++i) {
		int8_t type = fancy->operations[i].type;
		int num = fancy->operations[i].num;
		if (type == ADD) {
			curr_value = (curr_value + num) % mod;
		} else if (type == MULT) {
			curr_value = (int32_t)(((int64_t)curr_value * num) % mod);
		}
	}

	fancy->sequence[index].last_update = curr_update;
	fancy->sequence[index].value = curr_value;

	return curr_value;
}

void fancyFree(Fancy *fancy)
{
	free(fancy->sequence);
	free(fancy->operations);
	free(fancy);
}
