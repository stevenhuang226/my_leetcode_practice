#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int dn[4] = {1, -1, 0, 0};
int dm[4] = {0, 0, 1, -1};
int i, ii, d;

int **pacificAtlantic(int **heights, int heightsSize, int *heightsColSize, int *returnSize, int **returnColumnSizes)
{
	int m = heightsSize;
	int n = *heightsColSize;

	if (m == 1 && n == 1) {
		int **ans = malloc(1 * sizeof(int *));
		ans[0] = malloc(2 * sizeof(int));
		ans[0][0] = 0;
		ans[0][1] = 1;
		int *colSizes = malloc(1 * sizeof(int));
		colSizes[0] = 2;
		*returnColumnSizes = colSizes;
		return ans;
	}

	int8_t *visited_flat = calloc(m * n, sizeof(int8_t));
	int8_t **visited = malloc(m * sizeof(int8_t *));
	for (i = 0; i < m; i++) {
		visited[i] = visited_flat + i*n;
	}

	/* m,n */
	int *po_quene = malloc(4 * (m+n) * sizeof(int));
	int *po_next = malloc(4 * (m+n) * sizeof(int));
	int po_ptr = 0;
	int po_size;

	int *ao_quene = malloc(4 * (m+n) * sizeof(int));
	int *ao_next = malloc(4 * (m+n) * sizeof(int));
	int ao_ptr = 0;
	int ao_size;

	for (i = 0; i < n; i++) {
		if (visited[0][i] == 2) visited[0][i] = 3;
		else visited[0][i] = 1;
		po_quene[po_ptr*2 + 1] = i;
		po_quene[(po_ptr++)*2] = 0;
	}
	for (i = 0; i < m; i++) {
		if (visited[i][0] == 2) visited[i][0] = 3;
		else visited[i][0] = 1;
		po_quene[po_ptr*2 + 1] = 0;
		po_quene[(po_ptr++)*2] = i;
	}

	for (i = 0; i < n; i++) {
		if (visited[m-1][i] == 1) visited[m-1][i] = 3;
		else visited[m-1][i] = 2;
		ao_quene[ao_ptr*2 + 1] = i;
		ao_quene[(ao_ptr++)*2] = m-1;
	}
	for (i = 0; i < m; i++) {
		if (visited[i][n-1] == 1) visited[i][n-1] = 3;
		else visited[i][n-1] = 2;
		ao_quene[ao_ptr*2 + 1] = n-1;
		ao_quene[(ao_ptr++)*2] = i;
	}

	po_size = po_ptr;
	ao_size = ao_ptr;
	for (; po_size > 0 || ao_size > 0; ) {
		po_ptr = 0;
		ao_ptr = 0;
		for (i = 0; i < po_size; i++) {
			int am = po_quene[i*2];
			int an = po_quene[i*2 + 1];
			int h = heights[am][an];

			for (d = 0; d < 4; d++) {
				int nm = am + dm[d];
				int nn = an + dn[d];
				if (nm < 0 || nm >= m || nn < 0 || nn >= n) continue;
				int nh = heights[nm][nn];
				if (nh < h) continue;
				if (visited[nm][nn] == 2) {
					visited[nm][nn] = 3;
					continue;
				}
				if (visited[nm][nn]) continue;
				visited[nm][nn] = 1;
				po_next[po_ptr*2 + 1] = nn;
				po_next[(po_ptr++)*2] = nm;
			}
		}
		for (i = 0; i < ao_size; i++) {
			int am = ao_quene[i*2];
			int an = ao_quene[i*2 + 1];
			int h = heights[am][an];

			for (d = 0; d < 4; d++) {
				int nm = am + dm[d];
				int nn = an + dn[d];
				if (nm < 0 || nm >= m || nn < 0 || nn >= n) continue;
				int nh = heights[nm][nn];
				if (nh < h) continue;
				if (visited[nm][nn] == 1) {
					visited[nm][nn] = 3;
					continue;
				}
				if (visited[nm][nn]) continue;
				visited[nm][nn] = 2;
				ao_next[ao_ptr*2 + 1] = nn;
				ao_next[(ao_ptr++)*2] = nm;
			}
		}
		po_size = po_ptr;
		ao_size = ao_ptr;

		int *tmp;
		tmp = po_next;
		po_next = po_quene;
		po_quene = tmp;

		tmp = ao_next;
		ao_next = ao_quene;
		ao_quene = tmp;
	}

	int count = 0;
	int *ans_flat = malloc(m * n * 2 * sizeof(int));
	int **ans = malloc(m * n * sizeof(int *));

	int *colSizes = malloc(m * n * sizeof(int));

	for (i = 0; i < m; i++) {
		for (ii = 0; ii < n; ii++) {
			if (visited[i][ii] != 3) continue;
			ans[count] = ans_flat + count * 2;
			ans[count][0] = i;
			ans[count][1] = ii;
			colSizes[count] = 2;
			count++;
		}
	}

	*returnSize = count;
	*returnColumnSizes = colSizes;

	return ans;
}
