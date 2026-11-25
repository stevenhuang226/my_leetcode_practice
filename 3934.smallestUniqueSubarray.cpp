#include "shdstd-cpp.h"

using namespace std;

class Solution {
private:
	int64_t mod = 1e9 + 7;
	int64_t base = 10;

	int64_t spow(int64_t b, int64_t e) {
		int64_t res = 1;
		while (e) {
			if (e & 1) {
				res = res * b % mod;
			}
			b = b * b % mod;
			e >>= 1;
		}
		return res;
	}

	int8_t possibleUniqueLneght(const vector<int> &nums, int len) {
		int64_t h = 0;
		int l, r;
		l = r = 0;

		int64_t p = spow(10, len-1);

		for (; r < len; ++r) {
			h = ((h * base) + nums[r]) % mod;
		}

		unordered_map<int64_t, int> freq;

		++freq[h];
		for (; r < nums.size(); ++l, ++r) {
			h = ((h - (nums[l] * p) % mod) + mod) % mod;
			h = (h * base + nums[r]) % mod;

			++freq[h];
		}

		for (auto &[_, cnt] : freq) {
			if (cnt == 1) return true;
		}
		return false;
	}
public:
	int smallestUniqueSubarray(vector<int> &nums) {
		int size = nums.size();

		int BL, BR;
		BL = 1;
		BR = size;

		while (BL < BR) {
			int mid = (BL + BR) / 2;

			if (possibleUniqueLneght(nums, mid)) {
				BR = mid;
			} else {
				BL = mid+1;
			}
		}

		return BL;
	}
};
