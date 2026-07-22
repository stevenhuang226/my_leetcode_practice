#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
typedef struct {
	char type;
	int left;
	int right;
	int len;
} TypeSegment;

int *st_tree;

void build(int *merged, int curr, int left, int right)
{
	if (left == right) {
		st_tree[curr] = merged[left];
		return;
	}

	int mid = (left + right) / 2;

	build(merged, curr * 2 + 1, left, mid);
	build(merged, curr * 2 + 2, mid+1, right);

	st_tree[curr] = MAX(st_tree[curr*2+1], st_tree[curr*2+2]);
}

int query(int curr, int curr_left, int curr_right, int query_left, int query_right)
{
	if (query_left <= curr_left && query_right >= curr_right) {
		return st_tree[curr];
	}

	if (query_right < curr_left || query_left > curr_right) {
		return 0;
	}

	int mid = (curr_left + curr_right) / 2;
	int res_left = query(curr * 2 + 1, curr_left, mid, query_left, query_right);
	int res_right = query(curr * 2 + 2, mid+1, curr_right, query_left, query_right);

	return MAX(res_left, res_right);
}

int *maxActiveSectionsAfterTrade(char *s,
	int **queries, int queries_size, int *queries_col_size,
	int *ret_size)
{
	int len = strlen(s);

	int one_count = 0;
	for (int i = 0; i < len; ++i) {
		one_count += (s[i] == '1');
	}

	TypeSegment *source_segment = malloc(len * sizeof(TypeSegment));
	int seg_count = 0;

	int *zero_segs = malloc(len * sizeof(int));

	int zero_seg_count, one_seg_count;
	zero_seg_count = one_seg_count = 0;

	for (int i = 0; i < len; ++i) {
		char type = s[i];

		int start = i;
		while (i < len && s[i] == type) {
			++i;
		}
		--i;

		source_segment[seg_count].type = type;
		source_segment[seg_count].left = start;
		source_segment[seg_count].right = i;
		source_segment[seg_count].len = i - start + 1;

		if (type == '0') {
			zero_segs[zero_seg_count++] = seg_count;
		} else {
			++one_seg_count;
		}

		++seg_count;
	}

	if (zero_seg_count <= 1) {
		int *res = malloc(queries_size * sizeof(int));
		for (int i = 0; i < queries_size; ++i) {
			res[i] = one_count;
		}
		*ret_size = queries_size;
		return res;
	}

	int *map2left = malloc(len * sizeof(int));
	int *map2right = malloc(len * sizeof(int));
	memset(map2left, 0xff, len * sizeof(int));
	for (int i = 0; i < len; ++i) {
		map2right[i] = INT32_MAX;
	}

	int merged_count = zero_seg_count - 1;
	int *merged = malloc(merged_count * sizeof(int));
	for (int i = 0; i < merged_count; ++i) {
		int curr = zero_segs[i];
		int next = zero_segs[i+1];
		merged[i] = source_segment[curr].len + source_segment[next].len;

		map2left[source_segment[next].right] = i;
		map2right[source_segment[curr].left] = i;
	}
	free(zero_segs);

	for (int i = 0; i < len-1; ++i) {
		map2left[i+1] = MAX(map2left[i], map2left[i+1]);
	}
	for (int i = len-1; i > 0; --i) {
		map2right[i-1] = MIN(map2right[i], map2right[i-1]);
	}

	st_tree = malloc(merged_count * 4 * sizeof(int));

	build(merged, 0, 0, merged_count-1);

	int *res = malloc(queries_size * sizeof(int));

	for (int i = 0; i < queries_size; ++i) {
		int query_left = queries[i][0];
		int query_right = queries[i][1];

		int merged_left = map2right[query_left];
		int merged_right = map2left[query_right];

		int q_max = 0;
		if (merged_right - merged_left >= 0 && merged_right != INT32_MAX) {
			q_max = query(0, 0, merged_count - 1, merged_left, merged_right);
		}

		int left_seg, right_seg;

		int bs_left = 0;
		int bs_right = seg_count-1;
		while (bs_left < bs_right) {
			int mid = (bs_left + bs_right) / 2;

			if (source_segment[mid].right < query_left) {
				bs_left = mid+1;
			} else {
				bs_right = mid;
			}
		}
		left_seg = bs_left;

		bs_left = 0; bs_right = seg_count - 1;
		while (bs_left < bs_right) {
			int mid = (bs_left + bs_right) / 2;

			if (source_segment[mid].right < query_right) {
				bs_left = mid+1;
			} else {
				bs_right = mid;
			}
		}
		right_seg = bs_left;

		if (source_segment[left_seg].type == '0' &&
			left_seg + 2 < seg_count &&
			source_segment[left_seg+2].left <= query_right) {
			int left_len = source_segment[left_seg].right - query_left + 1;
			int right_len = MIN(query_right, source_segment[left_seg+2].right) - source_segment[left_seg+2].left + 1;

			q_max = MAX(q_max, left_len + right_len);
		}
		if (source_segment[right_seg].type == '0' &&
			right_seg - 2 >= 0 &&
			source_segment[right_seg-2].right >= query_left) {
			int right_len = query_right - source_segment[right_seg].left + 1;
			int left_len = source_segment[right_seg-2].right - MAX(query_left, source_segment[right_seg-2].left) + 1;

			q_max = MAX(q_max, left_len + right_len);
		}

		res[i] = one_count + q_max;
	}

	free(source_segment);
	free(map2left);
	free(map2right);
	free(st_tree);

	*ret_size = queries_size;
	return res;
}
