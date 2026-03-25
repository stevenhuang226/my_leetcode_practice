#include "shdstd.h"

#define MAX_NUM 1002

typedef struct {
	int *heap;
	int size;
	int capacity;
	int8_t *in_heap;

	int next_min;
} SmallestInfiniteSet;

void swap(int *l, int *r)
{
	int tmp = *r;
	*r = *l;
	*l = tmp;
	return;
}

void shift_up(int *heap, const int size, int index)
{
	while (index) {
		int parent_id = (index - 1) / 2;
		if (heap[parent_id] <= heap[index]) {
			return;
		}
		swap(&(heap[parent_id]), &(heap[index]));
		index = parent_id;
	}
	return;
}

void shift_down(int *heap, const int size, int index)
{
	for (;;) {
		int left = index * 2 + 1;
		int right = index * 2 + 2;

		int min_id = index;

		if (left < size && heap[left] < heap[min_id]) {
			min_id = left;
		}
		if (right < size && heap[right] < heap[min_id]) {
			min_id = right;
		}

		if (min_id == index) {
			return;
		}

		swap(&(heap[min_id]), &(heap[index]));
		index = min_id;
	}
	return;
}

SmallestInfiniteSet *smallestInfiniteSetCreate()
{
	SmallestInfiniteSet *obj = malloc(sizeof(SmallestInfiniteSet));
	obj->heap = malloc(MAX_NUM * sizeof(int));
	obj->in_heap = calloc(MAX_NUM, sizeof(int8_t));
	obj->capacity = MAX_NUM;
	obj->size = 0;
	obj->next_min = 1;

	return obj;
}

int smallestInfiniteSetPopSmallest(SmallestInfiniteSet *obj)
{
	int heap_min = INT32_MAX;
	if (obj->size > 0) {
		heap_min = obj->heap[0];
	}

	if (obj->next_min < heap_min) {
		return (obj->next_min)++;
	}

	int ret = obj->heap[0];
	obj->heap[0] = obj->heap[--(obj->size)];
	shift_down(obj->heap, obj->size, 0);

	obj->in_heap[ret] = false;

	return ret;
}

void smallestInfiniteSetAddBack(SmallestInfiniteSet *obj, int num)
{
	if (obj->next_min <= num) {
		return;
	}

	if (obj->in_heap[num]) {
		return;
	}

	obj->in_heap[num] = true;

	obj->heap[obj->size] = num;
	shift_up(obj->heap, obj->size, obj->size);
	++(obj->size);

	return;
}

void smallestInfiniteSetFree(SmallestInfiniteSet *obj)
{
	free(obj->in_heap);
	free(obj->heap);
	free(obj);
	return;
}
