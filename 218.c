#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int **merge(int **arr, int l,int r, int *size, int **out_flat)
{
	if ((r - l) <= 1) {
		int *ret_flat = malloc(4 * sizeof(int));
		int **ret = malloc(2 * sizeof(int *));
		ret[0] = ret_flat;
		ret[0][0] = arr[l][0];
		ret[0][1] = arr[l][2];
		ret[1] = ret_flat + 2;
		ret[1][0] = arr[l][1];
		ret[1][1] = 0;

		(*size) = 2;
		(*out_flat) = ret_flat;

		return ret;
	}
	/*
	 * it touch bottom, return with {{l,height}, {r,0}}
	 */

	int mid = (l + r) / 2;
	int l_size, r_size;
	int *flat_l = NULL, *flat_r = NULL;
	int **left = merge(arr, l, mid, &l_size, &flat_l);
	int **right = merge(arr, mid, r, &r_size, &flat_r);
	/*
	 * just the standar merge sort
	 */

	int lptr, rptr, ptr;
	lptr = rptr = ptr= 0;

	int *ret_flat = malloc((l_size + r_size) * 2 * sizeof(int));
	int **ret = malloc((l_size + r_size) * sizeof(int *));
	int i;
	for (i = 0; i < (l_size + r_size); ++i) {
		ret[i] = ret_flat + i * 2;
	}

	int curr_lh = 0, curr_rh = 0, prev_h = 0;
	/*
	 * using curr_lh and curr_rh to track left/right height
	 * prev_h used for tack lask critical point's height, void add new point with same height
	 */

	while (lptr < l_size && rptr < r_size) {
		int lx = left[lptr][0];
		int rx = right[rptr][0];

		int lh = left[lptr][1];
		int rh = right[rptr][1];

		int max_h;

		/*
		 * left-x smaller than right-x
		 */
		if (lx < rx) {
			curr_lh = lh;/* update curr_lh */
			max_h = MAX(curr_lh, curr_rh); /* max between left/right */
			if (max_h != prev_h) { /* height is different to last one */
				ret[ptr][0] = lx;
				ret[ptr++][1] = max_h; /* add new point */
				prev_h = max_h;
			}
			++lptr; /* doesn't matter height is equal to last one or not, because we had read this value, so jump to next one */
			continue;
		}
		if (rx < lx) {
			curr_rh = rh;/* update curr_rh */
			max_h = MAX(curr_lh, curr_rh); 
			if (max_h != prev_h) {
				ret[ptr][0] = rx;
				ret[ptr++][1] = max_h;
				prev_h = max_h;
			}
			++rptr;
			continue;
		}

		curr_lh = lh; curr_rh = rh; /* right/left height is equal, update both curr_l/rh */
		max_h = MAX(curr_lh, curr_rh);
		if (max_h != prev_h) { /* add point with both same value */
			ret[ptr][0] = lx;
			ret[ptr++][1] = max_h;
			prev_h = max_h;
		}
		++lptr; ++rptr;
	}

	/* if there is things left in left */
	while (lptr < l_size) {
		int x = left[lptr][0];
		int h = left[lptr][1];
		if (h != prev_h) {
			ret[ptr][0] = x;
			ret[ptr++][1] = h;
			prev_h = h;
		}
		++lptr;
	}
	/* if there is things left in right */
	while (rptr < r_size) {
		int x = right[rptr][0];
		int h = right[rptr][1];
		if (h != prev_h) {
			ret[ptr][0] = x;
			ret[ptr++][1] = h;
			prev_h = h;
		}
		++rptr;
	}

	free(left); /* **left */
	free(right); /* **right */
	free(flat_l); /* *flat_left */
	free(flat_r); /* *flat_right */

	(*size) = ptr;
	(*out_flat) = ret_flat;
	return ret;
}

int **getSkyline(int **buildings, int size, int *col_size, int *ret_size, int **ret_col_size)
{
	int merge_size;
	int *flat = NULL;
	int **res = merge(buildings, 0, size, &merge_size, &flat);

	(*ret_size) = merge_size;
	(*ret_col_size) = malloc(merge_size * sizeof(int));
	int i;
	for (i = 0; i < merge_size; ++i) {
		(*ret_col_size)[i] = 2;
	}

	return res;
}
