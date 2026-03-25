#include <stdlib.h>
#include <stdint.h>

#define HEAP_PARENT(i) (((i) - 1) / 2)
#define HEAP_LEFT(i) ((i) * 2 + 1)
#define HEAP_RIGHT(i) ((i) * 2 + 2)

typedef struct {
	void **data;
	uint32_t size;
	uint32_t capacity;
	int (*cmp)(const void *, const void *);
} MinHeap;

static inline void heap_swap(void **left, void **righ)
{
	void *tmp = *left;
	*left = *right;
	*right = tmp;
}

MinHeap *heap_create(uint32_t capacity,
		int (*cmp)(const void *, const void *))
{
	MinHeap *heap = malloc(sizeof(MinHeap));
	heap->data = malloc(capacity * sizeof(void *));
	heap->size = 0;
	heap->capacity = capacity;
	heap->cmp = cmp;
	return heap;
}

static void min_heap_shift_up(MinHeap *heap, uint32_t index)
{
	while (index > 0) {
		uint32_t parent = HEAP_PARENT(index);
		if (heap->cmp(heap->data[index], heap->data[parent]) >= 0) {
			break;
		}
		heap_swap(&heap->data[index], &heap->data[parent]);
		index = parent;
	}
}

static void min_heap_shift_down(MinHeap *heap, uint32_t index)
{
	for (;;) {
		uint32_t left = HEAP_LEFT(index);
		uint32_t right = HEAP_RIGHT(index);

		uint32_t min_id = index;

		if (left < heap->size &&
				heap->cmp(heap->data[left], heap->data[min_id]) < 0) {
			min_id = left;
		}

		if (right < heap->size &&
				heap->cmp(heap->data[right], heap->data[min_id]) < 0) {
			min_id = right;
		}

		if (min_id == index) {
			break;
		}

		heap_swap(&heap->data[index], &heap->data[min_id]);
		index = min_id;
	}
}

int8_t min_heap_push(MinHeap *heap, void *item)
{
	if (heap->size >= heap->capacity) {
		return -1;
	}

	heap->data[heap->size] = item;
	min_heap_shift_up(heap, heap->size);
	++(heap->size);
	return 0;
}

void *min_heap_pop(MinHeap *heap)
{
	if (heap->size == 0) {
		return NULL;
	}

	void *result = heap->data[0];

	--(heap->size);
	heap->data[0] = heap->data[heap->size];
	min_heap_shift_down(heap, 0);

	return result;
}

void *min_heap_top(const MinHeap *heap)
{
	if (heap->size == 0) {
		return NULL;
	}

	return heap->data[0];
}

int8_t min_heap_empty(const MinHeap *heap)
{
	return heap->size == 0;
}

void heap_free(MinHeap *heap)
{
	free(heap->data);
	free(heap);
}
