#include "shdstd.h"

/*
 *
 * not finished yet
 *
 */

#define MAX_HEAP 1000

typedef struct {
	int *data;
	uint32_t size;
	uint32_t capacity;
} SmallestInfiniteSet;

void swap(int *l, int *r)
{
	int tmp = *r;
	*r = *l;
	*l = tmp;
	return;
}

void shift_up(SmallestInfiniteSet *heap, int index)
{
	int *data = heap->data;
	while (index) {
		int parent = (index - 1) / 2;
		if (data[parent] < data[index]) {
			break;
		}
		swap(&(data[parent]), &(data[index]));
		index = parent;
	}
	return;
}

void shift_down(SmallestInfiniteSet *heap, int index)
{
	int *data = heap->data;
	int size = heap->size;

	for (;;) {
		int left = index * 2 + 1;
		int right = index * 2 + 2;

		int min_id = index;

		if (left < size && data[left] < data[min_id]) {
			min_id = left;
		}

		if (right < size && data[right] < data[min_id]) {
			min_id = right;
		}

		if (min_id == index) {
			break;
		}

		swap(&(data[min_id]), &(data[index]));

		index = min_id;
	}
	return;
}

SmallestInfiniteSet *smallestInfiniteSetCreate()
{
	SmallestInfiniteSet *obj = malloc(sizeof(SmallestInfiniteSet));
	obj->data = malloc(MAX_HEAP * sizeof(int));
	obj->size = 0;
	obj->capacity = MAX_HEAP;

	return obj;
}

int smallestInfiniteSetPopSmallest(SmallestInfiniteSet *heap)
{
	int ret = heap->data[0];
	--heap->size;
	heap->data[0] = heap->data[heap->size];
	shift_down(heap, 0);
	return ret;
}

void smallestInfiniteSetAddBack(SmallestInfiniteSet *heap, int new)
{
	heap->data[heap->size] = new;
	shift_up(heap, heap->size);
	++heap->size;
	return;
}

void smallestInfiniteSetFree(SmallestInfiniteSet *heap)
{
	free(heap->data);
	free(heap);
	return;
}
