#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

#define MAX_TYPE_SIZE 100

int comp(const void *a, const void *b)
{
	const char *left = *(const char **)a;
	const char *right = *(const char **)b;

	return strcmp(left, right);
}

char **validateCoupons(char **codes, int code_size, char **business_line, int business_size, bool *is_active, int is_active_size, int *p_ret_size)
{
	char available[] = "electronics\0grocery\0pharmacy\0restaurant\0";
	int available_size = 4;
	int available_ptr = 0;

	char trg_stack[MAX_TYPE_SIZE];
	char *trg = trg_stack;

	char **ret = malloc(code_size * sizeof(char *));
	int ret_size = 0;
	int last_size = 0;

	int t, i;
	for (t = 0; t < available_size; ++t) {
		int trg_ptr = 0;
		while (available[available_ptr] != '\0') {
			trg[trg_ptr++] = available[available_ptr++];
		}
		trg[trg_ptr] = '\0';
		available_ptr++;

		for (i = 0; i < is_active_size; ++i) {
			/* check active */
			if (! is_active[i]) {
				continue;
			}
			/* check business line */
			char *business = business_line[i];
			if (strcmp(trg, business) != 0) {
				continue;
			}

			/* check code */
			char *code = codes[i];
			if (code[0] == '\0') {
				continue;
			}
			int code_ptr = 0;
			char c;
			while ((c = code[code_ptr++]) != '\0') {
				if (! (
				(c >= '0' && c <= '9') ||
				(c >= 'A' && c <= 'Z') ||
				(c >= 'a' && c <= 'z') ||
				(c == '_')
				)) {
					code = NULL;
					break;
				}
			}
			if (code == NULL) {
				continue;
			}

			ret[ret_size++] = code;
		}

		int new_count = ret_size - last_size;

		if (new_count == 0) {
			continue;
		}

		qsort(ret + last_size, new_count, sizeof(char *), comp);

		last_size = ret_size;
	}

	*p_ret_size = ret_size;

	return ret;
}
