#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX2 47
#define MAX3 30
static int min_len[MAX2 + 3][MAX3 + 3];
static int8_t min_len_set = false;

int smin(const int a, const int b)
{
	return MIN(a, b);
}

void init()
{
	if (min_len_set)
		return;

	for (int i = 0; i < MAX2; ++i) {
		for (int i2 = 0; i2 < MAX3; ++i2) {
			min_len[i][i2] = INT32_MAX;
		}
	}

	min_len[0][0] = 0;

	for (int two = 0; two < MAX2; ++two) {
		for (int tree = 0; tree < MAX3; ++tree) {
			if (min_len[two][tree] == INT32_MAX)
				continue;

			min_len[two+1][tree] = smin(
				min_len[two+1][tree],
				min_len[two][tree] + 1);

			min_len[two][tree+1] = smin(
				min_len[two][tree+1],
				min_len[two][tree] + 1);

			min_len[two+2][tree] = smin(
				min_len[two+2][tree],
				min_len[two][tree] + 1);

			min_len[two+1][tree+1] = smin(
				min_len[two+1][tree+1],
				min_len[two][tree] + 1);

			min_len[two+3][tree] = smin(
				min_len[two+3][tree],
				min_len[two][tree] + 1);

			min_len[two][tree+2] = smin(
				min_len[two][tree+2],
				min_len[two][tree] + 1);
		}
	}

	min_len_set = true;
}

void req_sub(int *req, int d)
{
	switch (d) {
		case 2:
			req[2] -= 1;
			return;
		case 3:
			req[3] -= 1;
			return;
		case 4:
			req[2] -= 2;
			return;
		case 5:
			req[5] -= 1;
			return;
		case 6:
			req[2] -= 1;
			req[3] -= 1;
			return;
		case 7:
			req[7] -= 1;
			return;
		case 8:
			req[2] -= 3;
			return;
		case 9:
			req[3] -= 2;
			return;
		default:
			return;
	}
}

void req_add(int *req, int d)
{
	switch (d) {
		case 2:
			req[2] += 1;
			return;
		case 3:
			req[3] += 1;
			return;
		case 4:
			req[2] += 2;
			return;
		case 5:
			req[5] += 1;
			return;
		case 6:
			req[2] += 1;
			req[3] += 1;
			return;
		case 7:
			req[7] += 1;
			return;
		case 8:
			req[2] += 3;
			return;
		case 9:
			req[3] += 2;
			return;
		default:
			return;
	}
}

int min_req_len(int *req)
{
	int two = MAX(req[2], 0);
	int three = MAX(req[3], 0);
	int five = MAX(req[5], 0);
	int seven = MAX(req[7], 0);

	return min_len[two][three] + five + seven;
}

void build_suffix(char *bfr, int *req, int len)
{
	for (int i = 0; i < len; ++i) {
		for (int d = 1; d <= 9; ++d) {
			req_sub(req, d);

			int lim = len - i - 1;
			if (min_req_len(req) <= lim) {
				bfr[i] = d + '0';
				break;
			}

			req_add(req, d);
		}
	}
}

char *smallestNumber(char *num, int64_t t)
{
	init();

	int req[8] = {0};

	for (int i = 2; i <= 7; ++i) {
		while (t % i == 0) {
			++req[i];
			t /= i;
		}
	}

	if (t != 1)
		return "-1";

	int len = strlen(num);
	int first_zero = INT32_MAX;
	for (int i = 0; i < len; ++i) {
		int d = num[i] - '0';
		if (d == 0 && first_zero == INT32_MAX) {
			first_zero = i;
		}
		req_sub(&(req[0]), d);
	}

	if (req[2] <= 0 &&
		req[3] <= 0 &&
		req[5] <= 0 &&
		req[7] <= 0 &&
		first_zero == INT32_MAX) {
		return strdup(num);
	}

	char *buffer;

	for (int i = len-1; i >= 0; --i) {
		int right_len = len - i - 1;
		req_add(&(req[0]), num[i] - '0');
		for (int d = num[i] - '0' + 1; d <= 9; ++d) {
			req_sub(&(req[0]), d);
			if (first_zero >= i && min_req_len(&(req[0])) <= right_len) {
				buffer = malloc(right_len * sizeof(char));
				build_suffix(buffer, &(req[0]), right_len);

				char *res = malloc((i + right_len + 2) * sizeof(char));
				int r = 0;
				for (int i2 = 0; i2 < i; ++i2) {
					res[r++] = num[i2];
				}
				res[r++] = d + '0';
				for (int i2 = 0; i2 < right_len; ++i2) {
					res[r++] = buffer[i2];
				}
				res[r++] = '\0';
				free(buffer);
				return res;
			}
			req_add(&(req[0]), d);
		}
	}

	for (int new = len+1; ; ++new) {
		if (min_req_len(&(req[0])) > new)
			continue;

		char *res = malloc((new+1) * sizeof(char));
		build_suffix(res, &(req[0]), new);
		res[new] = '\0';
		return res;
	}

	return NULL;
}
