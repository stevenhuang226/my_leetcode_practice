#include "shdstd.h"

typedef struct Node Node;
struct Node {
	int key; //num
	uint32_t value; //index in array
	Node *next;
};

typedef struct {
	Node **buckets;
	uint32_t buckets_size;

	int *array; //num
	int arr_size;
} RandomizedSet;

RandomizedSet *randomizedSetCreate()
{
	int max_size = 2e5 + 2;

	RandomizedSet *obj = malloc(sizeof(RandomizedSet));
	obj->buckets_size = max_size;
	obj->buckets = malloc(max_size * sizeof(Node *));
	for (int i = 0; i < max_size; ++i) {
		obj->buckets[i] = NULL;
	}
	obj->array = malloc(max_size * sizeof(int));
	obj->arr_size = 0;

	return obj;
}

uint32_t hash(int value, int32_t size)
{
	return (uint32_t)value % size;
}

int randomizedSetFind(RandomizedSet *obj, int key)
{
	uint32_t hashed = hash(key, obj->buckets_size);
	Node *node = obj->buckets[hashed];
	while (node != NULL) {
		if (node->key == key) {
			return (int)node->value;
		}
		node = node->next;
	}
	return -1;
}

int8_t randomizedSetEdit(RandomizedSet *obj, int key, uint32_t new)
{
	uint32_t hashed = hash(key, obj->buckets_size);

	Node *node = obj->buckets[hashed];
	while (node != NULL) {
		if (node->key == key) {
			node->value = new;
			return true;
		}
		node = node->next;
	}
	return false;
}

bool randomizedSetInsert(RandomizedSet *obj, int value)
{
	if (randomizedSetFind(obj, value) >= 0) {
		return false;
	}

	uint32_t hashed = hash(value, obj->buckets_size);
	Node *old_node = obj->buckets[hashed];
	obj->buckets[hashed] = malloc(sizeof(Node));
	obj->buckets[hashed]->next = old_node;
	obj->buckets[hashed]->key = value;
	obj->buckets[hashed]->value = (uint32_t)(obj->arr_size);
	
	obj->array[(obj->arr_size)++] = value;

	return true;
}

bool randomizedSetRemove(RandomizedSet *obj, int value)
{
	int old_index = randomizedSetFind(obj, value);
	if (old_index < 0) {
		return false;
	}

	--(obj->arr_size);
	if (obj->arr_size != old_index) {
		int edit_key = obj->array[obj->arr_size];
		randomizedSetEdit(obj, edit_key, old_index);
		obj->array[old_index] = edit_key;
	}


	uint32_t hashed = hash(value, obj->buckets_size);

	Node *prev = NULL;
	Node *curr = obj->buckets[hashed];

	while (curr->key != value) {
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL) {
		obj->buckets[hashed] = curr->next;
	} else {
		prev->next = curr->next;
	}

	free(curr);

	return true;
}

int randomizedSetGetRandom(RandomizedSet *obj)
{
	int random_num = rand() % obj->arr_size;

	return obj->array[random_num];
}

void randomizedSetNodeFree(Node *node)
{
	if (node == NULL) {
		return;
	}
	free(node->next);
	return;
}

void randomizedSetFree(RandomizedSet *obj)
{
	for (int i = 0; i < obj->buckets_size; ++i) {
		randomizedSetNodeFree(obj->buckets[i]);
	}

	free(obj->array);

	free(obj);

	return;
}
