#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

#define INF 100000000
#define NEG_INF (-100000000)

#define MAX_CHILD_NUM 160
#define MAX_STATE 2

#define BUY 1
#define NOT_BUY 0

typedef struct {
	int size;
	int *arr;
} Tree_Node;

int *g_present;
int *g_future;
Tree_Node *tree;
int ***dp;

int g_budget;

void init_dp_u(int u)
{
	for (int cost = 0; cost <= g_budget; ++cost) {
		dp[u][BUY][cost] = NEG_INF;
		dp[u][NOT_BUY][cost] = NEG_INF;
	}
}

void dfs(int u)
{
	init_dp_u(u);

	dp[u][NOT_BUY][0] = 0;

	int cost_u = g_present[u];
	int profit_u = g_future[u] - cost_u;

	if (cost_u <= g_budget) {
		dp[u][BUY][cost_u] = profit_u;
	}

	int i;
	for (i = 0; i < tree[u].size; ++i) {
		int v = tree[u].arr[i];

		dfs(v);

		int tmp_dp[MAX_STATE][g_budget+1];
		for (int cost = 0; cost <= g_budget; ++cost) {
			tmp_dp[BUY][cost] = NEG_INF;
			tmp_dp[NOT_BUY][cost] = NEG_INF;
		}

		for (int u_buy = NOT_BUY; u_buy < MAX_STATE; ++u_buy) {
		for (int cu = 0; cu <= g_budget; ++cu) {
			int curr_profit = dp[u][u_buy][cu];
			if (curr_profit == NEG_INF) {
				continue;
			}

			for (int v_buy = NOT_BUY; v_buy < MAX_STATE; ++v_buy) {
			for (int cv = 0; cv <= g_budget; ++cv) {
				int extra_profit = dp[v][v_buy][cv];
				if (extra_profit == NEG_INF) {
					continue;
				}

				int extra_cost = 0;

				if (v_buy == BUY) {
					if (u_buy == BUY) {
						extra_cost = g_present[v] / 2;
					} else {
						extra_cost = g_present[v];
					}
				}

				int tmp_cost = cu + cv + extra_cost;
				if (tmp_cost > g_budget) {
					continue;
				}

				int tmp_profit = curr_profit + extra_profit;
				tmp_dp[u_buy][tmp_cost] = MAX(tmp_dp[u_buy][tmp_cost], tmp_profit);
			}
			}
		}
		}

		for (int c = 0; c <= g_budget; ++c) {
			dp[u][NOT_BUY][c] = tmp_dp[NOT_BUY][c];
			dp[u][BUY][c] = tmp_dp[BUY][c];
		}
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

	dp = malloc(n * sizeof(int **));
	int **flat = malloc(n * MAX_STATE * sizeof(int *));
	int *flat_flat = malloc(n * MAX_STATE * (budget + 1) * sizeof(int));

	int i, i2;
	for (i = 0; i < n; ++i) {
		dp[i] = flat + i * MAX_STATE;
		for (i2 = 0; i2 < MAX_STATE; ++i2) {
			dp[i][i2] = flat_flat + (i * MAX_STATE + i2) * (budget + 1);
		}
	}

	tree = malloc(n * sizeof(Tree_Node));
	for (i = 0; i < n; ++i) {
		tree[i].arr = malloc(MAX_CHILD_NUM * sizeof(int));
		tree[i].size = 0;
	}

	for (i = 0; i < hierarchy_size; ++i) {
		int employee = hierarchy[i][1] - 1;
		int boss = hierarchy[i][0] - 1;
		tree[boss].arr[(tree[boss].size)++] = employee;
	}

	dfs(0);

	int ans = 0;
	for (i = 0; i <= budget; ++i) {
		ans = MAX(ans, dp[0][BUY][i]);
	}

	return ans;
}
