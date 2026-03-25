#include "shdstd.h"

#define MAX_CHARS 30
#define CHAR_OFFSET (-('a'))


int8_t setted[MAX_CHARS];
int8_t *parent;

double *weight;

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

void merge(char c_mol, char c_den, double val)
{
	int8_t mol = c_mol + CHAR_OFFSET;
	int8_t den = c_den + CHAR_OFFSET;

	int8_t mol_root = find(mol);
	int8_t den_root = find(den);

	if (mol_root == den_root) {
		return;
	}

	parent[mol_root] = den_root;
	weight[mol_root] = val * weight[den] / weight[mol];
}

double query(char c_mol, char c_den)
{
	int8_t mol = c_mol + CHAR_OFFSET;
	int8_t den = c_den + CHAR_OFFSET;

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


	/* read from equeations and values*/
	for (int i = 0; i < equations_size; ++i) {
		char mol = equations[i][0][0];
		char den = equations[i][1][0];
		double val = values[i];

		merge(mol, den, val);
	}

	double *ret = malloc(queries_size * sizeof(double));

	for (int i = 0; i < queries_size; ++i) {
		char mol = queries[i][0][0];
		char den = queries[i][1][0];

		ret[i] = query(mol, den);
	}

	*p_ret_size = queries_size;

	return ret;
}
