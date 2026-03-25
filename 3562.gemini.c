#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define INF -1000000000000000000LL // A sufficiently small number representing unreachable states

// Adjacency List for the Tree
typedef struct Edge {
	int to;
	struct Edge* next;
} Edge;

// Structure to hold DP results for a node to pass up to parent
typedef struct {
	long long* dp_skip;   // Array for case: Parent didn't buy this node
	int sz_skip;          // Max budget used in dp_skip
	long long* dp_bought; // Array for case: Parent bought this node
	int sz_bought;        // Max budget used in dp_bought
} NodeResult;

// Global/Helper variables context
typedef struct {
	Edge** head;
	int* present;
	int* future;
	int budget;
} Context;

// Helper: Add edge to graph
void addEdge(Context* ctx, int u, int v) {
	Edge* e = (Edge*)malloc(sizeof(Edge));
	e->to = v;
	e->next = ctx->head[u];
	ctx->head[u] = e;
}

// Helper: Max function
long long max_ll(long long a, long long b) {
	return a > b ? a : b;
}

// Helper: Merge 'src' array into 'dest' array (Knapsack convolution)
// dest: In/Out accumulator array
// dest_sz: Current valid max index in dest
// src: Child array to merge
// src_sz: Current valid max index in src
// limit: Global budget limit
// Returns: New valid max index (size)
int merge(long long* dest, int dest_sz, long long* src, int src_sz, int limit) {
	// We need a temporary buffer to avoid overwriting needed values
	int new_sz = dest_sz + src_sz;
	if (new_sz > limit) new_sz = limit;

	// Allocate temp buffer initialized to INF
	long long* temp = (long long*)malloc((new_sz + 1) * sizeof(long long));
	for (int i = 0; i <= new_sz; i++) temp[i] = INF;

	// Convolve: temp[i+j] = max(temp[i+j], dest[i] + src[j])
	for (int i = 0; i <= dest_sz; i++) {
		if (dest[i] == INF) continue;
		// Optimization: loop j based on limits
		int max_j = (limit - i < src_sz) ? (limit - i) : src_sz;
		for (int j = 0; j <= max_j; j++) {
			if (src[j] == INF) continue;
			long long val = dest[i] + src[j];
			if (val > temp[i + j]) {
				temp[i + j] = val;
			}
		}
	}

	// Copy back to dest
	for (int i = 0; i <= new_sz; i++) {
		dest[i] = temp[i];
	}

	free(temp);
	return new_sz;
}

// DFS Function to compute DP
NodeResult dfs(Context* ctx, int u) {
	// 1. Initialize Accumulators
	// We use accumulators to merge children results before deciding for u
	// agg_if_u_bought: Merging children assuming u is bought (children use their 'bought' table)
	// agg_if_u_skip: Merging children assuming u is skipped (children use their 'skip' table)

	long long* agg_if_u_bought = (long long*)malloc((ctx->budget + 1) * sizeof(long long));
	long long* agg_if_u_skip = (long long*)malloc((ctx->budget + 1) * sizeof(long long));

	// Init with INF, base case 0 cost = 0 profit
	for(int i = 0; i <= ctx->budget; i++) agg_if_u_bought[i] = agg_if_u_skip[i] = INF;
	agg_if_u_bought[0] = 0;
	agg_if_u_skip[0] = 0;

	int sz_agg_bought = 0;
	int sz_agg_skip = 0;

	// 2. Process Children
	Edge* e = ctx->head[u];
	while (e != NULL) {
		int v = e->to;
		NodeResult child_res = dfs(ctx, v);

		// Merge child results into accumulators
		sz_agg_bought = merge(agg_if_u_bought, sz_agg_bought, child_res.dp_bought, child_res.sz_bought, ctx->budget);
		sz_agg_skip = merge(agg_if_u_skip, sz_agg_skip, child_res.dp_skip, child_res.sz_skip, ctx->budget);

		// Free child memory immediately
		free(child_res.dp_bought);
		free(child_res.dp_skip);
		e = e->next;
	}

	// 3. Construct Result for Node u
	NodeResult res;
	res.dp_bought = (long long*)malloc((ctx->budget + 1) * sizeof(long long));
	res.dp_skip = (long long*)malloc((ctx->budget + 1) * sizeof(long long));
	for(int i = 0; i <= ctx->budget; i++) res.dp_bought[i] = res.dp_skip[i] = INF;

	// -- Construct dp_skip (Parent of u didn't buy u) --
	// Cost of u is FULL price
	int cost_full = ctx->present[u-1]; // 0-indexed
	long long profit_full = (long long)ctx->future[u-1] - cost_full;

	// Choice A: Don't buy u (Use agg_if_u_skip)
	for (int i = 0; i <= sz_agg_skip; i++) {
		if (agg_if_u_skip[i] != INF) {
			res.dp_skip[i] = max_ll(res.dp_skip[i], agg_if_u_skip[i]);
		}
	}
	int cur_sz_skip = sz_agg_skip;

	// Choice B: Buy u (Full) (Use agg_if_u_bought + u's cost/profit)
	if (cost_full <= ctx->budget) {
		for (int i = 0; i <= sz_agg_bought; i++) {
			if (agg_if_u_bought[i] == INF) continue;
			if (i + cost_full <= ctx->budget) {
				long long val = agg_if_u_bought[i] + profit_full;
				if (val > res.dp_skip[i + cost_full]) {
					res.dp_skip[i + cost_full] = val;
				}
				if (i + cost_full > cur_sz_skip) cur_sz_skip = i + cost_full;
			}
		}
	}
	res.sz_skip = cur_sz_skip;

	// -- Construct dp_bought (Parent of u bought u) --
	// Cost of u is HALF price
	int cost_half = ctx->present[u-1] / 2;
	long long profit_half = (long long)ctx->future[u-1] - cost_half;

	// Choice A: Don't buy u (Use agg_if_u_skip) - SAME as above
	for (int i = 0; i <= sz_agg_skip; i++) {
		if (agg_if_u_skip[i] != INF) {
			res.dp_bought[i] = max_ll(res.dp_bought[i], agg_if_u_skip[i]);
		}
	}
	int cur_sz_bought = sz_agg_skip;

	// Choice B: Buy u (Half) (Use agg_if_u_bought + u's cost/profit)
	if (cost_half <= ctx->budget) {
		for (int i = 0; i <= sz_agg_bought; i++) {
			if (agg_if_u_bought[i] == INF) continue;
			if (i + cost_half <= ctx->budget) {
				long long val = agg_if_u_bought[i] + profit_half;
				if (val > res.dp_bought[i + cost_half]) {
					res.dp_bought[i + cost_half] = val;
				}
				if (i + cost_half > cur_sz_bought) cur_sz_bought = i + cost_half;
			}
		}
	}
	res.sz_bought = cur_sz_bought;

	// Cleanup accumulators
	free(agg_if_u_bought);
	free(agg_if_u_skip);

	return res;
}

long long maxProfit(int n, int* present, int presentSize, int* future, int futureSize, int** hierarchy, int hierarchySize, int* hierarchyColSize, int budget) {
	// 1. Setup Context and Graph
	Context ctx;
	ctx.budget = budget;
	ctx.present = present;
	ctx.future = future;
	ctx.head = (Edge**)calloc(n + 1, sizeof(Edge*)); // 1-based indexing for nodes

	// Build Graph (Adjacency List)
	for (int i = 0; i < hierarchySize; i++) {
		// hierarchy[i] = [u, v] where u is boss of v
		int u = hierarchy[i][0];
		int v = hierarchy[i][1];
		addEdge(&ctx, u, v);
	}

	// 2. Run DFS from Root (Employee 1)
	NodeResult root_res = dfs(&ctx, 1);

	// 3. Get Answer
	// Employee 1 (CEO) has no boss, so they pay full price.
	// We look at root_res.dp_skip (corresponds to "Parent didn't buy" -> Full Price logic for current node)
	long long max_profit = 0;
	for (int i = 0; i <= root_res.sz_skip; i++) {
		if (root_res.dp_skip[i] > max_profit) {
			max_profit = root_res.dp_skip[i];
		}
	}

	// 4. Cleanup
	free(root_res.dp_bought);
	free(root_res.dp_skip);
	for (int i = 1; i <= n; i++) {
		Edge* e = ctx.head[i];
		while (e) {
			Edge* temp = e;
			e = e->next;
			free(temp);
		}
	}
	free(ctx.head);

	return max_profit;
}
