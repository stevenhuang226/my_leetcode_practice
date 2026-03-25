#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct {
	int a;
	int b;
} Cell;

typedef struct {
	int *data;
	uint32_t size;
	uint32_t capacity;
	int64_t sum;
} Heap;


void swap(int *l, int *r)
{
	int tmp = *l;
	*l = *r;
	*r = tmp;
}

void shift_up(int *heap, int index)
{
	while (index) {
		int parent = (index - 1) / 2;

		if (heap[parent] <= heap[index]) {
			return;
		}

		swap(&(heap[parent]), &(heap[index]));

		index = parent;
	}
}

void shift_down(int *heap, int size, int index)
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
}

void kMax_push(Heap *heap, int num)
{
	if (heap->size < heap->capacity) {
		heap->data[heap->size] = num;
		shift_up(heap->data, heap->size);
		++(heap->size);
		heap->sum += (int64_t)num;
		return;
	}

	int heap_min = heap->data[0];

	if (num <= heap_min) {
		return;
	}

	heap->data[0] = heap->data[heap->size - 1];
	shift_down(heap->data, heap->size, 0);

	heap->sum -= (int64_t)heap_min;

	heap->data[heap->size - 1] = num;
	shift_up(heap->data, heap->size - 1);

	heap->sum += (int64_t)num;
}

int comp(const void *l, const void *r)
{
	Cell cell_l = *(Cell *)l;
	Cell cell_r = *(Cell *)r;

	return cell_r.b - cell_l.b;
}

int64_t maxScore(int *nums1, int size, int *nums2, int nums2_size, int k)
{
	Cell *cells = malloc(size * sizeof(Cell));
	for (int i = 0; i < size; ++i) {
		int na = nums1[i];
		int nb = nums2[i];

		cells[i].a = na;
		cells[i].b = nb;
	}

	qsort(cells, size, sizeof(Cell), comp);

	Heap mini_heap;
	mini_heap.data = malloc(k * sizeof(int));
	mini_heap.size = 0;
	mini_heap.capacity = k;
	mini_heap.sum = 0;

	int64_t max = INT64_MIN;

	int i;

	for (i = 0; i < k - 1; ++i) {
		int n1 = cells[i].a;
		kMax_push(&mini_heap, n1);
	}

	for ( ; i < size; ++i) {
		int n1 = cells[i].a;
		int n2 = cells[i].b;
		kMax_push(&mini_heap, n1);

		max = MAX(max, mini_heap.sum * (int64_t)n2);
	}

	free(mini_heap.data);
	free(cells);

	return max;
}
