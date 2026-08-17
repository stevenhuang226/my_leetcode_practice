#include "shdstd-cpp.h"

using namespace std;

class Solution{
private:
	vector<vector<int>> memo;
	vector<int> prefix;

	int dfs(int L, int R) {
		if (L == R) {
			return 0;
		}

		if (memo[L][R] >= 0) {
			return memo[L][R];
		}

		int best = 0;
		for (int i = L; i < R; ++i) {
			int leftSum = prefix[i+1] - prefix[L];
			int rightSum = prefix[R+1] - prefix[i+1];

			if (leftSum < rightSum) {
				best = max(best, leftSum + dfs(L, i));
			} else if (rightSum < leftSum) {
				best = max(best, rightSum + dfs(i+1, R));
			} else if (leftSum == rightSum) {
				best = max(best, leftSum + max(dfs(L, i), dfs(i+1, R)));
			}
		}

		return memo[L][R] = best;
	}
public:
	int stoneGameV(vector<int> &stoneValue) {
		int sz = stoneValue.size();

		prefix.resize(sz + 1);
		prefix[0] = 0;
		for (int i = 0; i < sz; ++i) {
			prefix[i+1] = prefix[i] + stoneValue[i];
		}

		memo.assign(sz, vector<int>(sz, -1));

		return dfs(0, sz-1);
	}
};
