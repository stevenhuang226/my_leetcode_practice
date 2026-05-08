#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int exp_max = 0;

int *adj_head;
int *adj_next;
int *adj_to;
int edge_count;

int *spf;

int *build_spf(int lim)
{
	int *ret = malloc(lim * sizeof(int));

	for (int i = 0; i < lim; ++i) {
		ret[i] = i;
	}
	for (int i = 2; i * i < lim; ++i) {
		if (ret[i] != i) continue;

		for (int mul = i * i; mul < lim; mul += i) {
			if (ret[mul] == mul) {
				ret[mul] = i;
			}
		}
	}

	return ret;
}

static inline void adj_append(const int from, const int to)
{
	adj_to[edge_count] = to;
	adj_next[edge_count] = adj_head[from];
	adj_head[from] = edge_count;
	++edge_count;
}

int minJumps(int *nums, int size)
{
	exp_max = size;
	for (int i = 0; i < size; ++i) {
		exp_max = MAX(exp_max, nums[i]);
	}
	exp_max += 8;

	int8_t *visited = calloc(1, size * sizeof(int8_t));

	spf = build_spf(exp_max);

	adj_head = malloc(exp_max * sizeof(int));
	adj_next = malloc(exp_max * 2 * sizeof(int));
	adj_to = malloc(exp_max * 2 * sizeof(int));
	edge_count = 0;

	memset(adj_head, 0xff, exp_max * sizeof(int));

	for (int i = 0; i < size; ++i) {
		int num = nums[i];
		adj_append(num, i);
	}

	int *queue = malloc(size * sizeof(int));
	int q_size = 0;
	int *next = malloc(size * sizeof(int));
	int front = 0;

	visited[size-1] = true;
	queue[q_size++] = size-1;

	int step = 0;
	int best = -1;
	while (q_size > 0) {
		for (int i = 0; i < q_size; ++i) {
			int curr_id = queue[i];
			int curr_num = nums[curr_id];

			if (curr_id == 0) {
				best = step;
				break;
			}

			if (curr_id+1 < size && !visited[curr_id+1]) {
				visited[curr_id+1] = true;
				next[front++] = curr_id+1;
			}
			if (curr_id-1 >= 0 && !visited[curr_id-1]) {
				visited[curr_id-1] = true;
				next[front++] = curr_id-1;
			}

			if (adj_head[curr_num] < 0) continue;

			while (curr_num > 1) {
				int prime = spf[curr_num];

				int nx = adj_head[prime];
				adj_head[prime] = -1;
				while (nx >= 0) {
					int to = adj_to[nx];
					nx = adj_next[nx];

					if (!visited[to]) {
						visited[to] = true;
						next[front++] = to;
					}
				}

				while (curr_num % prime == 0) {
					curr_num /= prime;
				}
			}
		}

		if (best >= 0) {
			break;
		}

		int *tmp = queue;
		queue = next;
		next = tmp;

		q_size = front;
		front = 0;

		++step;
	}

	free(queue);
	free(next);
	free(adj_head);
	free(adj_next);
	free(adj_to);
	free(spf);

	return best;
}
