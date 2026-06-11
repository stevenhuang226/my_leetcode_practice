#include "shdstd.h"


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int exp_max = 5e4 + 8;
int exp_log = 16 + 1;

typedef struct {
	int64_t val;
	int l;
	int r;
} Node;

typedef struct {
	int capacity;
	int size;

	Node data[];
} Heap;

Heap *mh_create(int size)
{
	Heap *heap = malloc(sizeof(Heap) + size * sizeof(Node));

	heap->capacity = size;
	heap->size = 0;

	return heap;
}

void mh_push(Heap *heap, int val, int l, int r)
{
	int curr = heap->size;
	++heap->size;

	heap->data[curr].val = val;
	heap->data[curr].l = l;
	heap->data[curr].r = r;

	while (curr) {
		int parent = (curr-1) >> 1;

		if (heap->data[parent].val >= heap->data[curr].val)
			break;

		Node tmp = heap->data[curr];

		heap->data[curr] = heap->data[parent];
		heap->data[parent] = tmp;

		curr = parent;
	}
}

Node mh_pop(Heap *heap)
{
	if (heap->size <= 0) {
		return (Node){0, -1, -1};
	}

	Node ret = heap->data[0];
	heap->data[0] = heap->data[--heap->size];

	int curr = 0;

	while (curr < heap->size) {
		int left = curr * 2 + 1;
		int right = curr * 2 + 2;

		int min_id = curr;

		if (left < heap->size &&
			heap->data[left].val > heap->data[min_id].val) {
			min_id = left;
		}
		if (right < heap->size &&
			heap->data[right].val > heap->data[min_id].val) {
			min_id = right;
		}

		if (min_id == curr)
			break;

		Node tmp = heap->data[min_id];
		heap->data[min_id] = heap->data[curr];
		heap->data[curr] = tmp;

		curr = min_id;
	}

	return ret;
}

int64_t maxTotalValue(int *nums, int size, int k)
{

	exp_max = size + 1;

	int64_t **st_max = malloc(size * sizeof(int64_t *));
	int64_t *st_max_flat = malloc(size * exp_log * sizeof(int64_t));

	int64_t **st_min = malloc(size * sizeof(int64_t *));
	int64_t *st_min_flat = malloc(size * exp_log * sizeof(int64_t));

	for (int i = 0; i < size; ++i) {
		st_max[i] = st_max_flat + i * exp_log;
		st_min[i] = st_min_flat + i * exp_log;
		st_max[i][0] = nums[i];
		st_min[i][0] = nums[i];
	}

	int *log_table = malloc(exp_max * sizeof(int));
	log_table[1] = 0;

	for (int i = 2; i <= size; ++i) {
		log_table[i] = log_table[i/2] + 1;
	}

	for (int lg = 1; lg < exp_log; ++lg) {
		int len = 1 << lg;

		for (int i = 0; i + len - 1 < size; ++i) {
			st_max[i][lg] = MAX(
					st_max[i][lg-1],
					st_max[i + (len >> 1)][lg-1]);

			st_min[i][lg] = MIN(
					st_min[i][lg-1],
					st_min[i + (len >> 1)][lg-1]);
		}
	}

	Heap *mh = mh_create(size+1);

	for (int l = 0; l < size; ++l) {
		int r = size-1;
		int len = r - l + 1;

		int lg = log_table[len];

		int64_t max = MAX(
				st_max[l][lg],
				st_max[r - (1 << lg) + 1][lg]);
		int64_t min = MIN(
				st_min[l][lg],
				st_min[r - (1 << lg) + 1][lg]);

		int64_t diff = max - min;

		mh_push(mh, diff, l, r);
	}

	int64_t res = 0;
	for (int i = 0; i < k; ++i) {
		Node max_node = mh_pop(mh);

		int l = max_node.l;
		int r = max_node.r-1;
		int len = r - l + 1;

		if (len > 0) {
			int lg = log_table[len];
			int64_t max = MAX(
					st_max[l][lg],
					st_max[r - (1 << lg) + 1][lg]);
			int64_t min = MIN(
					st_min[l][lg],
					st_min[r - (1 << lg) + 1][lg]);
			int64_t diff = max - min;
			mh_push(mh, diff, l, r);
		}

		res += max_node.val;
	}

	free(log_table);
	free(st_max_flat);
	free(st_max);
	free(st_min_flat);
	free(st_min);
	free(mh);

	return res;
}
