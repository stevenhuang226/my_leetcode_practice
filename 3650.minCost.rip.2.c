#include "shdstd.h"

#define INF32 (INT32_MAX / 4)

#define HEAP_PARENT(i) (((i) - 1) / 2)
#define HEAP_LEFT(i) ((i) * 2 + 1)
#define HEAP_RIGHT(i) ((i) * 2 + 2)

typedef struct {
	void **data;
	uint32_t size;
	uint32_t capacity;
	int (*cmp)(const void *, const void *);
} MinHeap;

static inline void heap_swap(void **l, void **r)
{
	void *tmp = *l;
	*l = *r;
	*r = tmp;
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

typedef struct {
	int cost;
	int node;
} History;

int *adj_to;
int *adj_next;
int *adj_head;
int *edge_weight;

int edges_count;

int cmp_History(const void *l, const void *r)
{
	return ((History *)l)->cost - ((History *)r)->cost;
}

void create_edge(int node_u, int node_v, int weight)
{
	adj_to[edges_count] = node_v;
	adj_next[edges_count] = adj_head[node_u];
	edge_weight[edges_count] = weight;
	adj_head[node_u] = edges_count;
	++edges_count;
}

int dijkstra(int nodes)
{
	MinHeap *queue = heap_create(nodes, cmp_History);
	History *dist = malloc(nodes * sizeof(History));
	for (int i = 0; i < nodes; ++i) {
		dist[i].cost = INF32;
		dist[i].node = i;
	}
	min_heap_push(queue, &(dist[0]));

	while (queue->size > 0) {
		History *from = (History *)min_heap_pop(queue);

		int next_index = adj_head[from->node];
		while (next_index >= 0) {
			int node = adj_to[next_index];
			int weight = edge_weight[next_index];
			next_index = adj_next[next_index];

			if (dist[node].cost <= from->cost + weight) {
				continue;
			}

			dist[node].cost = from->cost + weight;
			min_heap_push(queue, &(dist[node]));
		}
	}

	int last_cost = dist[nodes-1].cost;
	
	free(dist);
	heap_free(queue);

	return last_cost;
}

int minCost(int nodes, int **edges, int edges_size, int edges_col_size)
{
	adj_to = malloc(edges_size * 2 * sizeof(int));
	adj_next = malloc(edges_size * 2 * sizeof(int));
	adj_head = malloc(nodes * sizeof(int));
	edge_weight = malloc(edges_size * 2 * sizeof(int));
	edges_count = 0;

	for (int i = 0; i < edges_size; ++i) {
		int node_a = edges[i][0];
		int node_b = edges[i][1];
		int w = edges[i][2];

		create_edge(node_a, node_b, w);
		create_edge(node_b, node_a, w * 2);
	}

	int last_dist = dijkstra(nodes);

	int res = -1;
	if (last_dist != INF32) {
		res = last_dist;
	}

	free(adj_to);
	free(adj_next);
	free(adj_head);
	free(edge_weight);

	return res;
}
