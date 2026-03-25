#include "shdstd.h"

/*
 * I should not use int8_t on this case. But I'm lazy to edit this
 */

#define MAX_CHARS 50
#define STRING_MAX_SIZE 6

int8_t *parent;
double *weight;

char name[MAX_CHARS][STRING_MAX_SIZE];
int8_t name_size = 0;

int8_t get_id(char *s)
{
	int string_max = STRING_MAX_SIZE - 1;

	int id = 0;
	while (id < name_size) {
		if (strncmp(name[id], s, string_max) == 0) {
			return id;
		}
		++id;
	}
	return -1;
}

int8_t init_id(char *s)
{
	int get = get_id(s);
	const int name_limit = MAX_CHARS;
	const int string_max = STRING_MAX_SIZE - 1;
	if (get >= 0) {
		return get;
	}
	if (name_size < name_limit) {
		strncpy(name[name_size], s, string_max);
		name[name_size][string_max] = '\0';
		++name_size;
		return name_size - 1;
	}
	return -1;
}

int8_t find(int8_t target)
{
	if (parent[target] == target) {
		return target;
	}

	int8_t old = parent[target];
	int8_t new = find(old);

	if (old == new) {
		return old;
	}

	weight[target] = weight[target] * weight[old];
	parent[target] = new;

	return new;
}

void merge(int8_t mol, int8_t den, double val)
{
	int8_t mol_root = find(mol);
	int8_t den_root = find(den);

	if (mol_root == den_root) {
		return;
	}

	parent[mol_root] = den_root;
	weight[mol_root] = val * weight[den] / weight[mol];
	return;

	/*
	 * 	want: mol_root / den_root for weight[mol_root]
	 *
	 * 	from: mol / den = val
	 * =>	(mol * mol_root * den_root) / (mol_root * den_root * den) = val
	 * (mol / mol_root) = weight[mol]
	 * (den_root / den) = 1 / weight[den]
	 * =>	weight[mol] * (mol_root / den_root) * (1 / weight[den]) = val
	 * =>	mol_root / den_root = val * weight[den] / weight[mol]
	 *
	 * why I know that ? NaN, that ChatGPT's idea.
	 */
}

double query(int8_t mol, int8_t den)
{
	if (mol < 0 || den < 0) {
		return (double)(-1.0f);
	}

	int8_t mol_root = find(mol);
	int8_t den_root = find(den);

	if (mol_root != den_root) {
		return (double)(-1.0f);
	}

	return weight[mol] / weight[den];
}

double *calcEquation(
	char ***equations, int equations_size, int *equations_col_size,
	double *values, int val_size,
	char ***queries, int queries_size, int *queries_col_size,
	int *p_ret_size)
{
	parent = malloc(MAX_CHARS * sizeof(int8_t));
	for (int i = 0; i < MAX_CHARS; ++i) {
		parent[i] = i;
	}

	weight = malloc(MAX_CHARS * sizeof(double));
	for (int i = 0; i < MAX_CHARS; ++i) {
		weight[i] = (double)1.0f;
	}

	for (int i = 0; i < MAX_CHARS; ++i) {
		name[i][0] = '\0';
	}
	name_size = 0;

	for (int i = 0; i < equations_size; ++i) {
		int8_t mol = init_id(equations[i][0]);
		int8_t den = init_id(equations[i][1]);
		double val = values[i];

		merge(mol, den, val);
	}

	double *ret = malloc(queries_size * sizeof(double));

	for (int i = 0; i < queries_size; ++i) {
		int8_t mol = get_id(queries[i][0]);
		int8_t den = get_id(queries[i][1]);

		ret[i] = query(mol, den);
	}

	free(parent);
	free(weight);

	*p_ret_size = queries_size;

	return ret;
}
