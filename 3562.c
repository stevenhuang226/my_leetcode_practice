#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007
#define NEG_INF -10000000
#define DEFAULT_VAL NEG_INF
#define MAX_EMPLOYEES_NUM 160

typedef struct {
	int *employees;
	int size;
} TreeNode;

typedef struct {
	int *half;	// assum parent will buy. So current node can have half price
	int half_max;
	int *full;	// assum parent will not buy. So current node cannot have half price. buy in full price.
	int full_max;
} Result;

TreeNode *tree;
int *g_present;
int *g_future;
int g_budget;

void merge(int *dest, int *p_dest_max, int *src, int *p_src_max)
{
	int dest_max = (*p_dest_max);
	int src_max = (*p_src_max);
	int new_max = MIN(dest_max + src_max, g_budget);

	int *buffer = malloc((new_max+1) * sizeof(int));

	for (int i = 0; i <= new_max; ++i) {
		buffer[i] = DEFAULT_VAL;
	}

	for (int dest_cost = 0; dest_cost <= dest_max; ++dest_cost) {
		if (dest[dest_cost] == DEFAULT_VAL) {
			continue;
		}

		int src_cost = 0;
		while (dest_cost + src_cost <= g_budget && src_cost <= src_max) {
			if (src[src_cost] == DEFAULT_VAL) {
				++src_cost;
				continue;
			}

			int sum_cost = dest_cost + src_cost;
			int sum_profit = dest[dest_cost] + src[src_cost];

			buffer[sum_cost] = MAX(buffer[sum_cost], sum_profit);

			++src_cost;
		}
	}

	for (int i = 0; i <= new_max; ++i) {
		dest[i] = buffer[i];
	}

	(*p_dest_max)  = new_max;

	return;
}

Result dfs(int current)
{
	int *children_half = malloc((g_budget + 1) * sizeof(int)); // all children assume current will buy. So they can have half price.
	int *children_full = malloc((g_budget + 1) * sizeof(int)); // all children assume current will not buy. They will buy with full price.
	int children_half_max = 0;
	int children_full_max = 0;

	for (int i = 0; i <= g_budget; ++i) {
		children_half[i] = DEFAULT_VAL;
		children_full[i] = DEFAULT_VAL;
	}
	children_half[0] = children_full[0] = 0; // cost == 0, profit == 0


	for (int e = 0; e < tree[current].size; ++e) {
		int child = tree[current].employees[e];
		Result child_res = dfs(child);
		/* merge child's result into children's */
		merge(children_half, &children_half_max,
		child_res.half, &child_res.half_max);
		merge(children_full, &children_full_max,
		child_res.full, &child_res.full_max);

		free(child_res.half);
		free(child_res.full);
	}

	Result curr_res;
	curr_res.half = malloc((g_budget+1) * sizeof(int)); // assume parent will buy. current will buy with half price.
	curr_res.full = malloc((g_budget+1) * sizeof(int)); // assume parent will not buy. current will buy in full price.
	for (int i = 0; i <= g_budget; ++i) {
		curr_res.half[i] = DEFAULT_VAL;
		curr_res.full[i] = DEFAULT_VAL;
	}

	/* current's additional price */
	int full_price = g_present[current];
	int half_price = full_price / 2;

	/* current's additional profit */
	int full_price_profit = g_future[current] - full_price;
	int half_price_profit = g_future[current] - half_price;

	/*
	 * before the loop. We do nothing
	 * If loop didn't change anything
	 * -> current doesn't buy
	 * -> data should come from children assume we didn't buy. aka children_full
	 */
	curr_res.half_max = children_full_max;
	curr_res.full_max = children_full_max;
	for (int cost = 0; cost <= children_full_max; ++cost) {
		curr_res.half[cost] = children_full[cost];
		curr_res.full[cost] = children_full[cost];
	}

	/*
	 * In this loop. If we change any thing.
	 * -> current buy.
	 * -> data should come from children assume we buy. aka children_half
	 */
	for (int children_cost = 0; children_cost <= children_half_max; ++children_cost) {
		/* this children_cost doesn't have porfit, skip */
		if (children_half[children_cost] == DEFAULT_VAL) {
			continue;
		}
		/*
		 * children's cost + current cost
		 * -> half: we buy in half price
		 * -> full: we buy in full price
		 */
		int half_sum_cost = children_cost + half_price;
		int full_sum_cost = children_cost + full_price;
		/* sum_cost under budget */
		if (half_sum_cost <= g_budget) {
			/* children profit + current's profit */
			int half_sum_profit = children_half[children_cost] + half_price_profit;
			curr_res.half[half_sum_cost] = MAX(curr_res.half[half_sum_cost], half_sum_profit);
			curr_res.half_max = MAX(curr_res.half_max, half_sum_cost);
		}
		if (full_sum_cost <= g_budget) {
			int full_sum_profit = children_half[children_cost] + full_price_profit;
			curr_res.full[full_sum_cost] = MAX(curr_res.full[full_sum_cost], full_sum_profit);
			curr_res.full_max = MAX(curr_res.full_max, full_sum_cost);
		}
	}

	free(children_half);
	free(children_full);

	return curr_res;
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
	int *tree_flat = malloc(n * MAX_EMPLOYEES_NUM * sizeof(int));
	for (int i = 0; i < n; ++i) {
		tree[i].employees = tree_flat + i * MAX_EMPLOYEES_NUM;
		tree[i].size = 0;
	}

	for (int i = 0; i < hierarchy_size; ++i) {
		int boss = hierarchy[i][0] - 1;
		int emp = hierarchy[i][1] - 1;
		tree[boss].employees[(tree[boss].size)++] = emp;
	}

	Result boss = dfs(0);

	int ans = 0;
	for (int cost = 0; cost <= boss.full_max; ++cost) {
		ans = MAX(ans, boss.full[cost]);
	}

	free(boss.half);
	free(boss.full);

	free(tree_flat);
	free(tree);

	return ans;
}
