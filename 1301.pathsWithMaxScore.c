#include "shdstd.h"

#define INF32 (INT32_MAX / 4)
#define NEG_INF32 -(INF32)
#define CODE(a, b) ((a) * cols + (b))

int mod = 1e9 + 7;

int dr[] = {+1,+1, 0};
int dc[] = { 0,+1,+1};

typedef struct {
	int value;
	int count;
} Node;

int *pathsWithMaxScore(char **board, int size, int *ret_size)
{
	int rows = size;
	int cols = size;
	Node *dp = malloc(rows * cols * sizeof(Node));
	memset(dp, 0x00, rows * cols * sizeof(Node));

	dp[0].value = 0;
	dp[0].count = 1;

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int curr_value = dp[CODE(r, c)].value;
			int curr_count = dp[CODE(r, c)].count;
			for (int i = 0; i < 3; ++i) {
				int nr = r + dr[i];
				int nc = c + dc[i];

				if (nr < 0 || nr >= rows)
					continue;
				if (nc < 0 || nc >= cols)
					continue;

				if (board[nr][nc] == 'X') {
					dp[CODE(nr, nc)].value = NEG_INF32;
					dp[CODE(nr, nc)].count = 0;
					continue;
				}

				int old_value = dp[CODE(nr, nc)].value;
				int old_count = dp[CODE(nr, nc)].count;

				int new_value;
				if (board[nr][nc] != 'S') {
					new_value = (curr_value + board[nr][nc] - '0') % mod;
				} else {
					new_value = curr_value;
				}

				if (old_value > new_value)
					continue;

				if (old_value == new_value) {
					dp[CODE(nr, nc)].count = (old_count + curr_count) % mod;
					continue;
				} else {
					dp[CODE(nr, nc)].value = new_value;
					dp[CODE(nr, nc)].count = curr_count;
				}
			}
		}
	}

	int val = dp[CODE(rows-1, cols-1)].value;
	int cnt = dp[CODE(rows-1, cols-1)].count;

	int *res = malloc(2 * sizeof(int));
	*ret_size = 2;

	res[0] = dp[CODE(rows-1, cols-1)].value;
	res[1] = dp[CODE(rows-1, cols-1)].count;

	if (res[1] == 0) {
		res[0] = 0;
	}

	free(dp);

	return res;
}
