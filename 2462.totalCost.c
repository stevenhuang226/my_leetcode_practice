#include "shdstd.h"

typedef struct {
	int *data;
	uint32_t size;
	uint32_t capacity;
} Heap;

void swap(int *l, int *r)
{
	int tmp = *l;
	*l = *r;
	*r = tmp;
}

void shift_up(int *data, int index)
{
	while (index) {
		int parent = (index - 1) / 2;

		if (data[parent] <= data[index]) {
			return;
		}

		swap(&(data[parent]), &(data[index]));
		index = parent;
	}
}

void shift_down(int *data, int size, int index)
{
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
			return;
		}

		swap(&(data[min_id]), &(data[index]));
		index = min_id;
	}
}

void heap_push(Heap *heap, int num)
{
	heap->data[heap->size] = num;
	shift_up(heap->data, heap->size);
	++(heap->size);
}

int heap_pop(Heap *heap)
{
	int ret = heap->data[0];
	--(heap->size);
	heap->data[0] = heap->data[heap->size];
	shift_down(heap->data, heap->size, 0);
	return ret;
}

int64_t totalCost(int *costs, int size, int k, int candidates)
{
	Heap left;
	Heap right;

	left.data = malloc(candidates * sizeof(int));
	left.size = 0;
	left.capacity = candidates;

	right.data = malloc(candidates * sizeof(int));
	right.size = 0;
	right.capacity = candidates;

	int l_ptr = 0;
	int r_ptr = size - 1;

	for (int i = 0; i < candidates && l_ptr <= r_ptr; ++i) {
		heap_push(&left, costs[l_ptr++]);
		if (l_ptr > r_ptr) break;
		heap_push(&right, costs[r_ptr--]);
	}

	int64_t sum = 0;
	for (int i = 0; i < k; ++i) {
		int left_min = INT32_MAX;
		int right_min = INT32_MAX;
		if (left.size > 0) {
			left_min = left.data[0];
		}
		if (right.size > 0) {
			right_min = right.data[0];
		}

		if (left_min <= right_min) {
			heap_pop(&left);
			sum += (int64_t)left_min;
			if (l_ptr <= r_ptr) {
				heap_push(&left, costs[l_ptr++]);
			}
		} else {
			heap_pop(&right);
			sum += (int64_t)right_min;
			if (r_ptr >= l_ptr) {
				heap_push(&right, costs[r_ptr--]);
			}
		}
	}

	free(left.data);
	free(right.data);

	return sum;
}
