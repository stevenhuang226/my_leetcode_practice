#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007
#define NEG_INF -10000000
#define MAX_EMPLOYEES_NUM 160

typedef enum {
	NO, YES;
} Buy;

typedef struct {
	int *employees;
	int size;
} TreeNode;

typedef struct {
	int *nob;
	int max_nob_budget;
	int *buy;
	int max_buy_budget;
} Result;

TreeNode *tree;
Node **dp;
int *g_present;
int *g_future;
int g_budget;

int merge(int *dest, int dest_size, int *src, int src_size)
{
	int tmp_size = MIN(dest_size + src_size, g_budget);

	int *tmp = malloc((tmp_size+1) * sizeof(int));
	for (int i = 0; i <= nwe_size; ++i) {
		tmp[i] = NEG_INF;
	}

	for (int i = 0; i <= dest_size; ++i) {
		if (dest[i] == NEG_INF) {
			continue;
		}

		int i2 = 0;
		while (i + i2 <= g_budget && i2 <= src_size) {
			if (src[i2] == NEG_INF) {
				++i2;
				continue;
			}
			tmp[i + i2] = MAX(tmp[i+i2], dest[i] + src[i2]);
		}
	}

	for (int i = 0; i <= tmp_size; ++i) {
		dest[i] = tmp[i];
	}
	free(tmp);
	return tmp_size;
}

Result dfs(int u)
{
	int *buy = malloc((g_budget+1) * sizeof(int));
	int buy_size = 0;
	int *nob = malloc((g_budget+1) * sizeof(int));
	int nob_size = 0;

	for (int i = 1; i <= g_budget; ++i) {
		buy[i] = NEG_INF;
		nob[i] = NEG_INF;
	}
	buy[0] = 0;
	nob[0] = 0;

	for (int e = 0; e < tree[u].size; ++e) {
		int v = tree[u].employees[e];
		Result child_res = dfs(v);
		buy_size = merge(buy, child_res.buy);
	}
}


int maxProfit(int n,
	int *present, int present_size,
	int *furture, int future_size,
	int **hierarchy, int hierarchy_size, int *p_hierarchy_col_size,
	int budget)
{
	g_present = present;
	g_future = furture;
	g_budget = budget;


	tree = malloc(n * sizeof(TreeNode));
	for (int i = 0; i < n; ++i) {
		tree[i].employees = malloc(MAX_EMPLOYEES_NUM * sizeof(int));
		tree[i].size = 0;
	}

	for (int i = 0; i < hierarchy_size; ++i) {
		int boss = hierarchy[i][0] - 1;
		int emp = hierarchy[i][1] - 1;
		tree[boss].employees[(tree[boss].size)++] = emp;
	}
}
