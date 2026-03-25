#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
typedef struct {
	int y;
	int8_t delta;
	int x_left;
	int x_right;
} Event;

typedef struct {
	int count;
	double covered;
} SegmentNode;

Event *events;
int events_size;

SegmentNode *tree;

double *x_coord;
int x_count;

int comp_double(const void *a, const void *b)
{
	double diff = *(double *)a - *(double *)b;
	return (diff < 0) ? -1 : (diff > 0);
}

int comp_event(const void *a, const void *b)
{
	double diff = ((Event *)a)->y - ((Event *)b)->y;
	return (diff < 0) ? -1 : (diff > 0);
}

void pull_up(int id, int left, int right)
{
	if (tree[id].count > 0) {
		tree[id].covered = x_coord[right] - x_coord[left];
		return;
	}
	if (right - left == 1) {
		tree[id].covered = 0.0;
		return;
	}

	double left_covered = tree[id * 2].covered;
	double right_covered = tree[id * 2 + 1].covered;

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

double area_below(double y_limit)
{
	memset(tree, 0x00, sizeof(SegmentNode) * 4 * x_count);

	double area = 0.0;
	double prev = events[0].y;

	for (int i = 0; i < events_size; ++i) {
		double curr = events[i].y;

		curr = MIN(curr, y_limit);

		double delta = curr - prev;
		if (delta > 0) {
			area += tree[1].covered * delta;
			prev = curr;
		}

		if (events[i].y > y_limit) break;

		update_range(1, 0, x_count - 1, events[i].x_left, events[i].x_right, events[i].delta);
	}

	return area;
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

	qsort(x_values, x_values_size, sizeof(double), comp_double);

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

		int left = 0;
		int right = 0;

		while (x_coord[left] != x) ++left;
		while (x_coord[right] != x + len) ++right;

		events[i * 2].x_left = left;
		events[i * 2].x_right = right;

		events[i * 2 + 1].x_left = left;
		events[i * 2 + 1].x_right = right;
	}

	qsort(events, events_size, sizeof(Event), comp_event);

	tree = calloc(4 * x_count, sizeof(SegmentNode));

	double low = events[0].y;
	double high = events[events_size - 1].y;

	double total_area = area_below(high);

	while (high - low > 1e-6) {
		double mid = (low + high) / 2;
		double below = area_below(mid);

		if (below * 2 < total_area) {
			low = mid;
		} else {
			high = mid;
		}
	}

	free(events);
	free(x_coord);
	free(tree);

	return low;
}
