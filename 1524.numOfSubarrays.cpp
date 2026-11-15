#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int64_t mod = 1e9 + 7;
public:
	int numOfSubarrays(vector<int> &arr) {
		int odd = 0;
		int even = 1;
		int64_t res = 0;
		uint8_t p = 0;
		for (const int n : arr) {
			p ^= (n & 1);

			if (p) {
				res = (res + even) % mod;
				++odd;
			} else {
				res = (res + odd) % mod;
				++even;
			}
		}

		return res;
	}
};
