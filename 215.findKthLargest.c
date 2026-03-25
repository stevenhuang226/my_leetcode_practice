#include "shdstd.h"

typedef struct {
	int *data;
	uint32_t size;
	uint32_t capacity;
} MiniHeap;

void swap(int *left, int *right)
{
	int tmp = *left;
	*left = *right;
	*right = tmp;
}

void shit_up(MiniHeap *heap, int index)
{
	int *data = heap->data;
	while (index) {
		int parent = (index - 1) / 2;
		if (data[parent] <= data[index]) {
			break;
		}

		swap(&(data[parent]), &(data[index]));

		index = parent;
	}

	return;
}

void shift_down(MiniHeap *heap, int index)
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

void heap_push(MiniHeap *heap, int new)
{
	heap->data[heap->size] = new;
	shit_up(heap, heap->size);
	++heap->size;
}

int heap_pop(MiniHeap *heap)
{
	int ret = heap->data[0];
	--heap->size;
	heap->data[0] = heap->data[heap->size];
	shift_down(heap, 0);

	return ret;
}

int findKthLargest(int *nums, int size, int k)
{
	MiniHeap mini_heap;
	mini_heap.data = malloc(k * sizeof(int));
	mini_heap.size = 0;
	mini_heap.capacity = k;

	for (int i = 0; i < k; ++i) {
		mini_heap.data[i] = INT32_MIN;
	}

	for (int i = 0; i < size; ++i) {
		int num = nums[i];

		if (mini_heap.size < k) {
			heap_push(&mini_heap, num);
			continue;
		}
		if (num > mini_heap.data[0]) {
			heap_pop(&mini_heap);
			heap_push(&mini_heap, num);
		}
	}

	int res = heap_pop(&mini_heap);

	free(mini_heap.data);

	return res;
}
