#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int64_t mod = 1e9 + 7;
	static constexpr size_t szLim = 1e3 + 8;

	vector<int64_t> fact = vector<int64_t>(szLim);
	vector<int64_t> invFact = vector<int64_t>(szLim);
	int64_t modPow(int64_t base, int64_t e) {
		int64_t res = 1;
		while (e) {
			if (e & 1) {
				res = (res * base) % mod;
			}
			base = (base * base) % mod;
			e >>= 1;
		}
		return res;
	}

	void initFact() {
		fact[0] = 1;
		for (int i = 0; i < szLim - 1; ++i) {
			fact[i+1] = fact[i] * (i+1) % mod;
		}
		invFact[szLim-1] = modPow(fact[szLim-1], mod-2);

		for (int i = szLim-1; i > 0; --i) {
			invFact[i-1] = (invFact[i] * i) % mod;
		}
	}

	int64_t comb(int n, int k) {
		return (fact[n] * invFact[k]) % mod * (invFact[n-k]) % mod;
	}

	int64_t dfs(vector<int> &arr) {
		size_t sz = arr.size();
		if (sz <= 2)
			return 1;

		int root = arr[0];

		vector<int> left, right;

		for (int i = 1; i < sz; ++i) {
			if (arr[i] < root) {
				left.push_back(arr[i]);
			} else {
				right.push_back(arr[i]);
			}
		}

		int64_t leftWays = dfs(left);
		int64_t rightWays = dfs(right);

		return comb(sz-1, left.size()) * leftWays % mod * rightWays % mod;
	}
public:
	int numOfWays(vector<int> &nums) {
		initFact();

		int64_t total = dfs(nums);

		return total - 1;
	}
};
