#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
typedef struct {
	int64_t y;
	int8_t delta;
	int x_left;
	int x_right;
} Event;

typedef struct {
	int count;
	int64_t covered;
} SegmentNode;

Event *events;
int events_size;

SegmentNode *tree;

int64_t *x_coord;
int x_count;

int comp64(const void *a, const void *b)
{
	int64_t diff = *(int64_t *)a - *(int64_t *)b;
	return (diff < 0) ? -1 : (diff > 0);
}

int comp_event(const void *a, const void *b)
{
	double diff = ((Event *)a)->y - ((Event *)b)->y;
	return (diff < 0) ? -1 : (diff > 0);
}

int lower_bound_64(int64_t *arr, int size, double target)
{
	int left = 0;
	int right = size;
	while (left < right) {
		int mid = (left + right) / 2;
		if (arr[mid] < target) {
			left = mid + 1;
		} else {
			right = mid;
		}
	}
	return left;
}

void pull_up(int id, int left, int right)
{
	if (tree[id].count > 0) {
		tree[id].covered = x_coord[right] - x_coord[left];
		return;
	}
	if (right - left == 1) {
		tree[id].covered = 0;
		return;
	}

	int64_t left_covered = tree[id * 2].covered;
	int64_t right_covered = tree[id * 2 + 1].covered;

	tree[id].covered = left_covered + right_covered;
}

void update_range(int id, int left, int right, int new_left, int new_right, int delta)
{
	if (new_right <= left || new_left >= right) return;

	if (new_left <= left && new_right >= right) {
		tree[id].count += delta;
		pull_up(id, left, right);
		return;
	}

	int mid = (left + right) / 2;
	update_range(id * 2, left, mid, new_left, new_right, delta);
	update_range(id * 2 + 1, mid, right, new_left, new_right, delta);
	pull_up(id, left, right);
}

int64_t *layer_y;
int64_t *layer_width;
int64_t *prefix_area;

int layer_size;
int64_t sweep_end_y;

void build_sweep()
{
	memset(tree, 0, x_count * 4 * sizeof(SegmentNode));

	layer_y = malloc(events_size * sizeof(int64_t));
	layer_width = malloc(events_size * sizeof(int64_t));
	prefix_area = malloc((events_size + 1) * sizeof(int64_t));

	int64_t prev = events[0].y;
	int idx = 0;

	for (int i = 0; i < events_size; ++i) {
		int64_t curr = events[i].y;
		int64_t delta = curr - prev;

		if (delta > 0) {
			layer_y[idx] = prev;
			layer_width[idx] = tree[1].covered;
			++idx;
			prev = curr;
		}

		update_range(1, 0, x_count - 1, events[i].x_left, events[i].x_right, events[i].delta);
	}

	layer_size = idx;
	sweep_end_y = events[events_size - 1].y;

	prefix_area[0] = 0.0;
	for (int i = 0; i < layer_size; ++i) {
		int64_t next_y = (i + 1 < layer_size)
			? layer_y[i+1]
			: sweep_end_y;
		int64_t h = next_y - layer_y[i];
		prefix_area[i + 1] = prefix_area[i] + layer_width[i] * h;
	}
}

double separateSquares(int **squares, int size, int *col_size)
{
	events_size = size * 2;
	events = malloc(events_size * sizeof(Event));

	double *x_values = malloc(size * 2 * sizeof(double));
	int x_values_size = 0;

	for (int i = 0; i < size; ++i) {
		double x = squares[i][0];
		double y = squares[i][1];
		double len = squares[i][2];

		x_values[x_values_size++] = x;
		x_values[x_values_size++] = x + len;

		events[i * 2].y = y;
		events[i * 2].delta = +1;

		events[i * 2 + 1].y = y + len;
		events[i * 2 + 1].delta = -1;
	}

	qsort(x_values, x_values_size, sizeof(double), comp64);

	x_coord = malloc(x_values_size * sizeof(double));
	x_count = 0;
	x_coord[x_count++] = x_values[0];
	for (int i = 0; i < x_values_size - 1; ++i) {
		if (x_values[i] != x_values[i+1]) {
			x_coord[x_count++] = x_values[i+1];
		}
	}

	free(x_values);

	for (int i = 0; i < size; ++i) {
		double x = squares[i][0];
		double len = squares[i][2];

		int left = lower_bound_64(x_coord, x_count, x);
		int right = lower_bound_64(x_coord, x_count, x + len);

		events[i * 2].x_left = left;
		events[i * 2].x_right = right;

		events[i * 2 + 1].x_left = left;
		events[i * 2 + 1].x_right = right;
	}

	qsort(events, events_size, sizeof(Event), comp_event);

	tree = malloc(4 * x_count * sizeof(SegmentNode));

	build_sweep();

	int64_t total_area = prefix_area[layer_size];

	double ret;

	for (int i = 0; i < layer_size; ++i) {
		int64_t curr_area = prefix_area[i];
		int64_t next_area = prefix_area[i+1];

		if (2 * next_area < total_area) {
			continue;
		}

		double delta_h = (total_area - curr_area * 2) / (double)(2 * layer_width[i]);
		ret = (double)layer_y[i] + delta_h;
		break;
	}

	free(events);
	free(x_coord);
	free(tree);
	free(layer_y);
	free(layer_width);
	free(prefix_area);

	return ret;
}
